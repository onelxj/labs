#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QWidget>
class QGridLayout;
class QPoint;
class QPushButton;

class Game : public QWidget
{
  Q_OBJECT
 public:
  Game(QWidget* parent = 0, int x = 0);
  void createButton(QPushButton*, int, int, int);

 private:
  int mode = 0;
  QList<QPushButton*> buttons;
  QList<int> numbers;
  QGridLayout* grid;
  QPoint path;
  QPixmap* px[15];
  void checkGameOver();
 public slots:
  void move();
};

#endif
