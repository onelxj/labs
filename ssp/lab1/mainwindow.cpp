#include "mainwindow.h"

#include <QLabel>
#include <QPainter>
#include <QThread>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  for (int i = 0; i < 2; i++) {
    QImage* img = new QImage(50, 50, QImage::Format_RGB32);
    imgs_.push_back(img);

    Qt::GlobalColor color = Qt::darkGreen;

    if (i) color = Qt::darkRed;

    QPainter painter(img);
    painter.fillRect(QRectF(0, 0, 50, 50), color);

    QLabel* label = new QLabel(this);
    label->setGeometry(100, 10 + 60 * i, 150, 60 + 60 * i);
    label->setPixmap(QPixmap::fromImage(*img));

    lbs_.push_back(label);
  }
}

MainWindow::~MainWindow()
{
  for (int i = 0; i < imgs_.size(); i++) delete imgs_[i];

  for (int i = 0; i < lbs_.size(); i++) delete lbs_[i];

  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  if (state) {
    QPainter painter(imgs_[0]);
    painter.fillRect(QRectF(0, 0, 50, 50), Qt::green);
    lbs_[0]->setPixmap(QPixmap::fromImage(*imgs_[0]));

    QPainter painter2(imgs_[1]);
    painter2.fillRect(QRectF(0, 0, 50, 50), Qt::darkRed);
    lbs_[1]->setPixmap(QPixmap::fromImage(*imgs_[1]));

    state = false;
  } else {
    QPainter painter(imgs_[0]);
    painter.fillRect(QRectF(0, 0, 50, 50), Qt::darkGreen);
    lbs_[0]->setPixmap(QPixmap::fromImage(*imgs_[0]));

    QPainter painter2(imgs_[1]);
    painter2.fillRect(QRectF(0, 0, 50, 50), Qt::red);
    lbs_[1]->setPixmap(QPixmap::fromImage(*imgs_[1]));
    state = true;
  }
}

void MainWindow::on_pushButton_3_clicked() {
  lbs_[0]->setGeometry(lbs_[0]->x() + 1, lbs_[0]->y(), lbs_[0]->x() + 50,
                       lbs_[0]->y() + 60);
}

void MainWindow::on_pushButton_2_clicked() {
  lbs_[0]->setGeometry(lbs_[0]->x() - 1, lbs_[0]->y(), lbs_[0]->x() + 50,
                       lbs_[0]->y() + 60);
}

void MainWindow::on_pushButton_4_clicked() {
  QPixmap* px = new QPixmap(200, 200);
  QPainter painter(px);

  painter.fillRect(QRectF(0, 0, 200, 200), Qt::white);
  painter.drawEllipse(100, 100, 40, 40);

  ui->label->setPixmap(*px);
}

void MainWindow::on_pushButton_5_clicked() {
  QPixmap* px = new QPixmap(200, 200);
  QPainter painter(px);

  painter.fillRect(QRectF(0, 0, 200, 200), Qt::white);
  painter.drawRect(50, 50, 100, 50);

  ui->label->setPixmap(*px);
}

void MainWindow::on_pushButton_6_clicked() {
  QPixmap* px = new QPixmap(200, 200);
  QPainter painter(px);

  painter.fillRect(QRectF(0, 0, 200, 200), Qt::white);
  painter.drawLine(50, 50, 100, 50);
  painter.drawLine(100, 50, 50, 100);
  painter.drawLine(50, 100, 50, 50);

  ui->label->setPixmap(*px);
}

void MainWindow::on_pushButton_7_clicked() {
  QPixmap* px = new QPixmap(200, 200);
  QPainter painter(px);

  painter.fillRect(QRectF(0, 0, 200, 200), Qt::white);

  static int r = 20;
  painter.fillRect(QRectF(0, 0, 200, 200), Qt::white);
  painter.drawEllipse(100, 200 - r, r / 2, r / 2);
  ui->label_2->setPixmap(*px);
  r++;
}
