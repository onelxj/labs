#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <map>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_add_clicked();

  void on_view_clicked();

  void on_delete_2_clicked();

 private:
  void update();
  void GetSave(QString type);

  Ui::MainWindow *ui;
  QString mPath;
  std::map<std::string, std::string> mData;
};
#endif // MAINWINDOW_H
