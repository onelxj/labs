#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "Game.h"
class QHBoxLayout;
class QLabel;
class QLCDNumber;
class QSpinBox;
class QVBoxLayout;

namespace Ui {
class Form;
}

class Form : public QWidget
{
  Q_OBJECT

 public:
  explicit Form(QWidget* parent = 0, int x = 0);
  ~Form();
 public slots:
  void newGame();
  void exitGame();
 private slots:
 private:
  int mode = 0;
  Ui::Form* ui;
  Game* game;
  QHBoxLayout* settingsLayout;
  QVBoxLayout* layout;
  QSpinBox* cubesize;
  QTimer* timer;
};

#endif // FORM_H
