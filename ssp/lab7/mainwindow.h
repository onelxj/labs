#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sqlite3.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

 private:
  void SetupTable();
  std::string getTableName();
  std::string getWorkers(std::string table_name);
  std::string getAmount(std::string table_name);

  Ui::MainWindow *ui;
  sqlite3 *db;
};
#endif // MAINWINDOW_H
