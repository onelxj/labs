#include "mainwindow.h"

#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QTextStream>
#include <iostream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  mPath = "cfg.txt";

  GetSave("Load from file?");
  update();
}

void MainWindow::GetSave(QString type) {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Data managment", type,
                                QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    if (type == "Save to file?") {
      QFile file(mPath);
      file.open(QIODevice::WriteOnly);
      QTextStream stream(&file);

      for (auto& el : mData) {
        QString name = QString(el.first.c_str());
        QString number = QString(el.second.c_str());

        stream << name << " " << number << '\n';
      }

      file.close();
    } else {
      QFile file(mPath);
      file.open(QIODevice::ReadOnly);
      QTextStream input(&file);

      while (!input.atEnd()) {
        QString line = input.readLine();
        QStringList list = line.split(' ');

        mData.insert({list[0].toStdString(), list[1].toStdString()});
      }
      file.close();
    }
  }
}

MainWindow::~MainWindow() {
  GetSave("Save to file?");
  delete ui;
}

void MainWindow::update() {
  ui->listWidget->clear();
  for (auto& el : mData) {
    ui->listWidget->addItem(QString(el.first.c_str()));
  }
}

void MainWindow::on_add_clicked() {
  mData.insert({ui->lineEdit->text().toStdString(),
                ui->lineEdit_2->text().toStdString()});
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  update();
}

void MainWindow::on_view_clicked() {
  QString name = ui->listWidget->currentItem()->text();
  std::string number = mData.find(name.toStdString())->second;

  QMessageBox::information(this, "Number", QString(number.c_str()),
                           QMessageBox::Ok);
}

void MainWindow::on_delete_2_clicked() {
  QString name = ui->listWidget->currentItem()->text();
  mData.erase(mData.find(name.toStdString()));
  update();
}
