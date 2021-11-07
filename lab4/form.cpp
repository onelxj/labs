#include "form.h"

#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "ui_form.h"
#include "ui_mainwindow.h"

Form::Form(QWidget* parent, int x)
    : game(NULL), QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
  mode = x;
  layout = new QVBoxLayout(this);
  settingsLayout = new QHBoxLayout;

  QPushButton* newgame = new QPushButton();
  QPushButton* exitgame = new QPushButton();

  QPixmap newG(":/gelik/new.png");
  QPixmap exG(":/gelik/exit.png");
  QIcon newGIcon(newG);
  QIcon exGIcon(exG);
  newgame->setIcon(newGIcon);
  exitgame->setIcon(exGIcon);
  newgame->setIconSize(QSize(304, 70));
  exitgame->setIconSize(QSize(290, 70));

  connect(newgame, SIGNAL(clicked()), this, SLOT(newGame()));
  connect(exitgame, SIGNAL(clicked()), this, SLOT(exitGame()));

  settingsLayout->addWidget(newgame);
  settingsLayout->addWidget(exitgame);

  layout->setContentsMargins(2, 2, 2, 2);
  layout->addLayout(settingsLayout);
  newGame();

  setLayout(layout);
}

Form::~Form()
{
    delete ui;
}

void Form::newGame() {
  if (game) {
    layout->removeWidget(game);
    delete game;
  }

  game = new Game(this, mode);
  layout->addWidget(game);

  layout->update();

  game->hide();
  game->show();

  resize(sizeHint());
}

void Form::exitGame()
{
    MainWindow *f = new MainWindow();
    f->show();
    this->close();
}
