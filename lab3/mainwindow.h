#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  virtual void paintEvent(QPaintEvent *event);

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  void drawLine(QPoint x, QPoint y);
  void drawCircle(QPoint p, int radius);

  Ui::MainWindow *ui;
  bool line = false;
  bool circle = false;
};
#endif // MAINWINDOW_H
