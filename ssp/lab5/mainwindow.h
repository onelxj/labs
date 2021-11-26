#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_tableWidget_cellChanged(int row, int column);

  void on_pushButton_2_clicked();

 private:
  QVector<QVector<int>> GetSubData(int row, int col);

  Ui::MainWindow *ui;

  QVector<QVector<int>> data_;
};
#endif // MAINWINDOW_H
