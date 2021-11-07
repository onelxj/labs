#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QSlider>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

    class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_actionOpen_triggered();

  void on_actionPlay_triggered();

  void on_actionPause_triggered();

  void on_actionStop_triggered();

 private:
  Ui::MainWindow* ui;
  QMediaPlayer* player_;
  QVideoWidget* widget_;
  QProgressBar* bar_;
  QSlider* slider_;
    };
#endif // MAINWINDOW_H
