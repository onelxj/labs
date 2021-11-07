#include "Game.h"

#include <mainwindow.h>

#include <QFile>
#include <QGridLayout>
#include <QPainter>
#include <QPoint>
#include <QPushButton>
#include <QTextStream>
#include <QTime>
#include <QtGlobal>
#include <cstdlib>

#include "QMessageBox"

Game::Game(QWidget*, int x) {
  mode = x;
  grid = new QGridLayout(this);
  grid->setHorizontalSpacing(1);
  grid->setVerticalSpacing(1);
  grid->setContentsMargins(2, 2, 2, 2);

  if (!mode) {
    for (int i = 0; i < 15; i++) {
      if (i == 0)
        px[i] = new QPixmap(":/gelik/1.jpg");
      else if (i == 7)
        px[i] = new QPixmap(":/gelik/8.jpg");
      else if (i == 1)
        px[i] = new QPixmap(":/gelik/2.jpg");
      else if (i == 8)
        px[i] = new QPixmap(":/gelik/9.jpg");
      else if (i == 2)
        px[i] = new QPixmap(":/gelik/3.jpg");
      else if (i == 9)
        px[i] = new QPixmap(":/gelik/10.jpg");
      else if (i == 3)
        px[i] = new QPixmap(":/gelik/4.jpg");
      else if (i == 10)
        px[i] = new QPixmap(":/gelik/11.jpg");
      else if (i == 4)
        px[i] = new QPixmap(":/gelik/5.jpg");
      else if (i == 11)
        px[i] = new QPixmap(":/gelik/12.jpg");
      else if (i == 5)
        px[i] = new QPixmap(":/gelik/6.jpg");
      else if (i == 12)
        px[i] = new QPixmap(":/gelik/13.jpg");
      else if (i == 6)
        px[i] = new QPixmap(":/gelik/7.jpg");
      else if (i == 13)
        px[i] = new QPixmap(":/gelik/14.jpg");
      else if (i == 14)
        px[i] = new QPixmap(":/gelik/15.jpg");
    }
  } else {
    for (int i = 0; i < 15; i++) {
      QPixmap* map = new QPixmap(QSize(150, 150));
      map->fill(QColor::fromRgb(72, 72, 72));
      QPainter painter(map);
      painter.setFont(QFont("Arial", 24));
      painter.drawText(QPoint(70, 75), QString::number(i));
      px[i] = map;
    }
  }

  int n;
  do {
    numbers.clear();

    for (int i = 0; i < 15; i++) {
      do n = rand() % 15 + 1;
      while (numbers.contains(n));
      numbers << n;
    }

    n = 0;

    for (int i = 2; i <= 15; i++)
      for (int j = 0; j < numbers.indexOf(i); j++) {
        if (numbers[j] < i) {
          ++n;
        }
      }
  } while (n % 2 == 1);

  do path.setY(rand() % 4);
  while (n % 2 != path.y() % 2);

  path.setX(rand() % 4);

  n = 0;

  for (int y = 0; y < 4; ++y)
    for (int x = 0; x < 4; ++x) {
      if (path.x() == x && path.y() == y) continue;

      createButton(NULL, numbers[n++], x, y);
    }
  setLayout(grid);
}

void Game::move()
{
    int x, y, rs, cs;
    QPushButton* clickedBtn = static_cast<QPushButton*>(sender());

    grid->getItemPosition(grid->indexOf(clickedBtn), &y, &x, &rs, &cs);

    if ((path.x() == x && (path.y() == y + 1 || path.y() == y - 1)) ||
        (path.y() == y && (path.x() == x + 1 || path.x() == x - 1))) {
      grid->removeWidget(clickedBtn);
      createButton(clickedBtn, 0, path.x(), path.y());
      path = QPoint(x, y);
      checkGameOver();
    }
}

void Game::checkGameOver()
{
    Q_ASSERT(grid->count() == numbers.size());

    int i=1, n=0;

    for (int y = 0; y < grid->rowCount(); ++y)
      for (int x = 0; x < grid->columnCount(); ++x) {
        if (grid->itemAtPosition(y, x) == 0) continue;
        n = numbers.indexOf(i++);
        if (buttons[n] != (QPushButton*)grid->itemAtPosition(y, x)->widget())
          return;
      }

    if (path.y() == grid->rowCount() - 1 &&
        path.x() == grid->columnCount() - 1) {
      for (QList<QPushButton*>::const_iterator it = buttons.begin();
           it != buttons.end(); ++it)
        (*it)->setDisabled(true);
      QMessageBox::information(this, "message", "Win!");

      QFile file("data.txt");
      file.open(QIODevice::ReadWrite);
      QTextStream stream(&file);
      QString line = stream.readLine();
      int actual = 0;
      if (line.size() != 0) {
        actual = line.toInt();
      }
      int res = ++actual;

      stream << QString(res);
      file.close();
    }
}

void Game::createButton(QPushButton* b, int no, int x, int y) {
  QPushButton* btn = b;
  if (!btn) {
    btn = new QPushButton();
    buttons << btn;
    connect(btn, SIGNAL(clicked()), this, SLOT(move()));
    btn->setFixedSize(150, 150);

    QIcon ButtonIcon(*px[no - 1]);
    btn->setIcon(ButtonIcon);
    btn->setIconSize(QSize(150, 150));
  }
  grid->addWidget(btn, y, x);
}
