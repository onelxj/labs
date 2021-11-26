#include "mainwindow.h"

#include <QDateTime>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QDateTime cd = QDateTime::currentDateTime();
  qsrand(cd.toTime_t());

  ui->tableWidget->setShowGrid(true);
  ui->tableWidget->setRowCount(0);
  ui->tableWidget->setColumnCount(4);
  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget->verticalHeader()->setStretchLastSection(true);

  for (int i = 0; i < 4; i++) {
    ui->tableWidget->insertRow(i);
    data_.push_back(QVector<int>());
    for (int j = 0; j < 4; j++)
      data_[i].push_back(qrand() % ((20 + 1) + 20) - 20);

    ui->tableWidget->setItem(
        i, 0, new QTableWidgetItem(QString::number(data_[i][0])));
    ui->tableWidget->setItem(
        i, 1, new QTableWidgetItem(QString::number(data_[i][1])));
    ui->tableWidget->setItem(
        i, 2, new QTableWidgetItem(QString::number(data_[i][2])));
    ui->tableWidget->setItem(
        i, 3, new QTableWidgetItem(QString::number(data_[i][3])));
  }

  ui->tableWidget_2->setRowCount(0);
  ui->tableWidget_2->setColumnCount(3);
  ui->tableWidget_2->setShowGrid(true);

  for (int i = 0; i < 4; i++) {
    ui->tableWidget_2->insertRow(i);
    ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(""));
    ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(""));
    ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(""));
  }

  ui->tableWidget_2->setHorizontalHeaderLabels(
      QStringList() << trUtf8("row") << trUtf8("column") << trUtf8("table"));
  ui->tableWidget_2->setVerticalHeaderLabels(QStringList()
                                             << trUtf8("sum") << trUtf8("avg")
                                             << trUtf8("min") << trUtf8("max"));
  ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget_2->verticalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_tableWidget_cellChanged(int row, int column) {
  auto* item = ui->tableWidget->item(row, column);
  auto t = item->text().toStdString();

  for (int i = 0; i < t.size(); i++) {
    if (!isdigit(t[i]) && t[i] != '-') {
      item->setText(QString::number(data_[row][column]));
      return;
    }
  }

  data_[row][column] = std::stoi(t);
}

QVector<QVector<int>> MainWindow::GetSubData(int row, int col) {
  QVector<QVector<int>> data;

  for (int i = 0; i < row; i++) {
    data.push_back(QVector<int>());
  }

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) data[i].push_back(data_[i][j]);
  }

  return data;
}

void MainWindow::on_pushButton_2_clicked() {
  auto row = ui->lineEdit->text().toInt();
  auto col = ui->lineEdit_2->text().toInt();

  auto data = GetSubData(row, col);

  if (row == 1) {
    int sumStr = 0;
    int max = data[0][0];
    int min = data[0][0];
    for (int i = 0; i < data[0].size(); i++) {
      sumStr += data[0][i];

      if (data[0][i] < max) max = data[0][i];
      if (data[0][i] > min) min = data[0][i];
    }

    ui->tableWidget_2->item(0, 0)->setText(QString::number(sumStr));
    ui->tableWidget_2->item(1, 0)->setText(QString::number(sumStr * 1.0 / col));
    ui->tableWidget_2->item(2, 0)->setText(QString::number(max));
    ui->tableWidget_2->item(3, 0)->setText(QString::number(min));
  }

  if (col == 1) {
    int sumStr = 0;
    int max = data[0][0];
    int min = data[0][0];
    for (int i = 0; i < data.size(); i++) {
      sumStr += data[i][0];

      if (data[i][0] < max) max = data[i][0];
      if (data[i][0] > min) min = data[i][0];
    }

    ui->tableWidget_2->item(0, 1)->setText(QString::number(sumStr));
    ui->tableWidget_2->item(1, 1)->setText(QString::number(sumStr * 1.0 / row));
    ui->tableWidget_2->item(2, 1)->setText(QString::number(max));
    ui->tableWidget_2->item(3, 1)->setText(QString::number(min));
  }

  int sumStr = 0;
  int max = data[0][0];
  int min = data[0][0];
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      sumStr += data[i][j];

      if (data[i][j] < max) max = data[i][j];
      if (data[i][j] > min) min = data[i][j];
    }
  }

  ui->tableWidget_2->item(0, 2)->setText(QString::number(sumStr));
  ui->tableWidget_2->item(1, 2)->setText(QString::number(sumStr * 1.0 / row));
  ui->tableWidget_2->item(2, 2)->setText(QString::number(max));
  ui->tableWidget_2->item(3, 2)->setText(QString::number(min));
}
