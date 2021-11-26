#include "mainwindow.h"

#include <QStandardItemModel>
#include <QString>
#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  sqlite3_open("db.db", &db);
  SetupTable();
}

MainWindow::~MainWindow() {
  delete ui;
  sqlite3_close(db);
}

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

namespace {

int select_callback(void* p_data, int num_fields, char** p_fields,
                    char** p_col_names) {
  Records* records = static_cast<Records*>(p_data);
  try {
    records->emplace_back(p_fields, p_fields + num_fields);
  } catch (...) {
    // abort select on failure, don't let exception propogate thru sqlite3
    // call-stack
    return 1;
  }
  return 0;
}

Records select_stmt(const char* stmt, sqlite3* db) {
  Records records;
  char* errmsg;
  int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);

  return records;
}

}  // namespace

/////////////////////////////////////////////////////////////////////////////////

void MainWindow::SetupTable() {
  ui->tableWidget->setShowGrid(true);
  ui->tableWidget_2->setShowGrid(true);
  ui->tableWidget_3->setShowGrid(true);

  ui->tableWidget->setColumnCount(2);
  ui->tableWidget_2->setColumnCount(2);
  ui->tableWidget_3->setColumnCount(2);
  ui->tableWidget->setHorizontalHeaderLabels(QStringList() << trUtf8("Workers")
                                                           << trUtf8("Amount"));
  ui->tableWidget_2->setHorizontalHeaderLabels(
      QStringList() << trUtf8("Workers") << trUtf8("Amount"));
  ui->tableWidget_3->setHorizontalHeaderLabels(
      QStringList() << trUtf8("Workers") << trUtf8("Amount"));

  ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
  ui->tableWidget_3->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::on_pushButton_clicked() {
  ui->tableWidget->setRowCount(0);
  ui->tableWidget_2->setRowCount(0);
  ui->tableWidget_3->setRowCount(0);

  SetupTable();

  Records records = select_stmt("SELECT * FROM gems", db);

  int idx = 0;
  for (auto& rec : records) {
    ui->tableWidget->insertRow(idx);
    ui->tableWidget->setItem(
        idx, 0, new QTableWidgetItem(QString::fromStdString(rec[0])));
    ui->tableWidget->setItem(
        idx, 1, new QTableWidgetItem(QString::fromStdString(rec[1])));
    idx++;
  }

  records = select_stmt("SELECT * FROM gold", db);

  idx = 0;
  for (auto& rec : records) {
    ui->tableWidget_2->insertRow(idx);
    ui->tableWidget_2->setItem(
        idx, 0, new QTableWidgetItem(QString::fromStdString(rec[0])));
    ui->tableWidget_2->setItem(
        idx, 1, new QTableWidgetItem(QString::fromStdString(rec[1])));
  }

  records = select_stmt("SELECT * FROM silver", db);

  idx = 0;
  for (auto& rec : records) {
    ui->tableWidget_3->insertRow(idx);
    ui->tableWidget_3->setItem(
        idx, 0, new QTableWidgetItem(QString::fromStdString(rec[0])));
    ui->tableWidget_3->setItem(
        idx, 1, new QTableWidgetItem(QString::fromStdString(rec[1])));
  }
}

// Add
void MainWindow::on_pushButton_2_clicked() {
  auto workers = ui->lineEdit->text();
  auto amount = ui->lineEdit_2->text();

  if (!(workers.size() && amount.size())) {
    return;
  }

  auto table_name = getTableName();

  std::string sql = "INSERT INTO " + table_name + " VALUES('" +
                    workers.toStdString() + "', '" + amount.toStdString() +
                    "')";

  sqlite3_exec(db, sql.c_str(), nullptr, 0, nullptr);

  ui->lineEdit->setText("");
  ui->lineEdit_2->setText("");

  on_pushButton_clicked();
}

std::string MainWindow::getTableName() {
  auto current_tab = ui->tabWidget->currentIndex();
  if (!current_tab) {
    return "gems";
  } else if (current_tab == 1) {
    return "gold";
  } else {
    return "silver";
  }
}

std::string MainWindow::getWorkers(std::string table_name) {
  if (table_name == "gems") {
    auto s = ui->tableWidget->selectionModel()->selectedIndexes();
    if (s.size() == 0) {
      return "";
    }

    auto idx = s.at(0).row();

    return ui->tableWidget->item(idx, 0)->text().toStdString();
  } else if (table_name == "gold") {
    auto s = ui->tableWidget_2->selectionModel()->selectedIndexes();
    if (s.size() == 0) {
      return "";
    }

    auto idx = s.at(0).row();

    return ui->tableWidget_2->item(idx, 0)->text().toStdString();
  } else {
    auto s = ui->tableWidget_3->selectionModel()->selectedIndexes();
    if (s.size() == 0) {
      return "";
    }

    auto idx = s.at(0).row();

    return ui->tableWidget_3->item(idx, 0)->text().toStdString();
  }

  return "";
}

std::string MainWindow::getAmount(std::string table_name) {
  if (table_name == "gems") {
    auto s = ui->tableWidget->selectionModel()->selectedIndexes();
    if (s.size() == 0) {
      return "";
    }

    auto idx = s.at(0).row();

    return ui->tableWidget->item(idx, 1)->text().toStdString();
  } else if (table_name == "gold") {
    auto s = ui->tableWidget_2->selectionModel()->selectedIndexes();
    if (s.size() == 0) {
      return "";
    }

    auto idx = s.at(0).row();

    return ui->tableWidget_2->item(idx, 1)->text().toStdString();
  } else {
    auto s = ui->tableWidget_3->selectionModel()->selectedIndexes();
    if (s.size() == 0) {
      return "";
    }

    auto idx = s.at(0).row();

    return ui->tableWidget_3->item(idx, 1)->text().toStdString();
  }

  return "";
}

// remove
void MainWindow::on_pushButton_3_clicked() {
  std::string table_name = getTableName();

  auto workers = getWorkers(table_name);
  auto amount = getAmount(table_name);

  if (!(workers.size() && amount.size())) {
    return;
  }

  std::string sql = "DELETE FROM " + table_name +
                    " WHERE WorkersCount = " + workers +
                    " AND Amount = " + amount;
  sqlite3_exec(db, sql.c_str(), nullptr, 0, nullptr);

  on_pushButton_clicked();
}
