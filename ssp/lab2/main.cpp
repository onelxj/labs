#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
 QApplication a(argc, argv);
 a.setQuitOnLastWindowClosed(true);
  //При закрытии последнего окна освободить ресурсы приложения
  //и закрыть его
 MainWindow w; //Создаём,
 w.show(); //показываем виджет
 return a.exec(); //и запускаем цикл обработки событий приложения
}
