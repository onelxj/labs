#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  //  QMediaPlayer* player = new QMediaPlayer;
  //  QVideoWidget* widget = new QVideoWidget;

  //  player->setVideoOutput(widget);
  //  player->setMedia(QUrl::fromLocalFile(
  //      "/home/zakhar/c++/labs/lab5/2021-10-25 12-42-57.mp4"));

  //  widget->setGeometry(100, 100, 300, 400);
  //  widget->show();

  //  player->play();

  return a.exec();
}
