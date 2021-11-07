#include "mainwindow.h"

#include <QFile>
#include <QTextStream>

#include "QMessageBox"
#include "form.h"
#include "ui_form.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked() {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Exit",
                                "Do you really want to leave the game?",
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    close();
  }
}

void MainWindow::on_pushButton_clicked() {
  Form *f = new Form();
  f->show();
  this->close();
}

void MainWindow::on_pushButton_3_clicked() {
  QFile file("data.txt");
  file.open(QIODevice::ReadWrite);
  QTextStream stream(&file);
  QString line = stream.readLine();
  QMessageBox::information(
      this, "About", "Won " + (line.size() == 0 ? "0" : line) + " times.");
}

void MainWindow::on_pushButton_2_clicked() {
  Form *f = new Form(nullptr, 1);
  f->show();
  this->close();
}
