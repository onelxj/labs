#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  player_ = new QMediaPlayer(this);
  widget_ = new QVideoWidget(this);
  player_->setVideoOutput(widget_);

  this->setCentralWidget(widget_);

  slider_ = new QSlider(this);
  bar_ = new QProgressBar(this);
  slider_->setOrientation(Qt::Horizontal);

  ui->statusbar->addPermanentWidget(slider_);
  ui->statusbar->addPermanentWidget(bar_);

  connect(player_, &QMediaPlayer::durationChanged, slider_,
          &QSlider::setMaximum);
  connect(player_, &QMediaPlayer::positionChanged, slider_, &QSlider::setValue);

  connect(slider_, &QSlider::sliderMoved, player_, &QMediaPlayer::setPosition);

  connect(player_, &QMediaPlayer::durationChanged, bar_,
          &QProgressBar::setMaximum);
  connect(player_, &QMediaPlayer::positionChanged, bar_,
          &QProgressBar::setValue);
}

MainWindow::~MainWindow() {
  delete ui;
  delete widget_;
  delete slider_;
  delete player_;
  delete bar_;
}

void MainWindow::on_actionOpen_triggered() {
  QString filename =
      QFileDialog::getOpenFileName(this, "Open a File", "",
                                   "Video File(*.avi *.mp4 *.mpg);;"
                                   "All files (*.*)");

  on_actionStop_triggered();
  player_->setMedia(QUrl::fromLocalFile(filename));
  on_actionPlay_triggered();
}

void MainWindow::on_actionPlay_triggered() {
  player_->play();
  ui->statusbar->showMessage("Playing");
}

void MainWindow::on_actionPause_triggered() {
  player_->pause();
  ui->statusbar->showMessage("Paused");
}

void MainWindow::on_actionStop_triggered() {
  player_->stop();
  ui->statusbar->showMessage("Stopped");
}
