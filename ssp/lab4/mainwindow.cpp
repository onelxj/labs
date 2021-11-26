#include "mainwindow.h"

#include <set>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->tableWidget->setShowGrid(true);

  ui->tableWidget->setColumnCount(2);
  ui->tableWidget_2->setColumnCount(1);
  ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("Goods")
                                                           << trUtf8("Price"));
  ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << trUtf8("Cart"));

  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

  for (int i = 1; i < 6; i++) {
    QString name = "Good" + QString::number(i);
    auto price = (qrand() % ((1000 + 1) - 50) + 50);
    data.push_back({name, price});

    ui->tableWidget->insertRow(i - 1);
    ui->tableWidget->setItem(i - 1, 0, new QTableWidgetItem(name));
    ui->tableWidget->setItem(i - 1, 1,
                             new QTableWidgetItem(QString::number(price)));
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  auto str = ui->lineEdit->text();

  int id = -1;

  for (int i = 0; i < data.size(); i++) {
    if (str == data[i].first) {
      id = i;
      break;
    }
  }

  if (id == -1)
    ui->lineEdit->setText("Not found");
  else {
    ui->lineEdit->setText("");
    ui->tableWidget->selectRow(id);
  }
}

void MainWindow::on_pushButton_2_clicked() {
  auto sel = ui->tableWidget->selectionModel()->selectedIndexes();

  std::set<int> ids;
  for (auto& s : sel) {
    ids.insert(s.row());
  }

  for (auto id : ids) {
    ui->tableWidget_2->insertRow(rows);
    ui->tableWidget_2->setItem(rows++, 0, new QTableWidgetItem(data[id].first));
    price += data[id].second;
  }

  ui->label->setText(QString::number(price));
  ui->tableWidget->clearSelection();
}

void MainWindow::on_pushButton_3_clicked() {
  auto sel = ui->tableWidget_2->selectionModel()->selectedIndexes();

  std::set<int> ids;
  for (auto& s : sel) {
    ids.insert(s.row());
  }

  for (auto id : ids) {
    auto name = ui->tableWidget_2->itemAt(0, id)->text();

    for (int i = 0; i < data.size(); i++) {
      if (data[i].first == name) {
        price -= data[i].second;
        break;
      }
    }
    ui->tableWidget_2->removeRow(id);
    rows--;
    ui->tableWidget_2->setRowCount(rows);
  }
  ui->label->setText(QString::number(price));
}
