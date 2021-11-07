#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
  if (line) {
    drawLine({ui->lineEdit->text().toInt(), ui->lineEdit_2->text().toInt()},
             {ui->lineEdit_3->text().toInt(), ui->lineEdit_4->text().toInt()});

    line = false;
  }
  if (circle) {
    drawCircle({ui->lineEdit_5->text().toInt(), ui->lineEdit_6->text().toInt()},
               ui->lineEdit_7->text().toInt());
    circle = false;
  }
}

void MainWindow::drawLine(QPoint p1, QPoint p2) {
  clearMask();
  QPainter painter(this);
  QPen pen;
  pen.setWidth(10);
  painter.setPen(pen);

  int deltaX = abs(p2.x() - p1.x());
  int deltaY = abs(p2.y() - p1.y());
  int signX = p1.x() < p2.x() ? 1 : -1;
  int signY = p1.y() < p2.y() ? 1 : -1;
  int error = deltaX - deltaY;

  int x1 = p1.x(), x2 = p2.x(), y1 = p1.y(), y2 = p2.y();

  painter.drawPoint(QPoint(x2, y2));
  while (x1 != x2 || y1 != y2) {
    painter.drawPoint(QPoint(x1, y1));
    int error2 = error * 2;
    if (error2 > -deltaY) {
      error -= deltaY;
      x1 += signX;
    }
    if (error2 < deltaX) {
      error += deltaX;
      y1 += signY;
    }
  }
}

void MainWindow::drawCircle(QPoint p, int radius) {
  clearMask();
  QPainter painter(this);
  QPen pen;
  pen.setWidth(10);
  painter.setPen(pen);

  int x0 = p.x(), y0 = p.y();

  int x = 0;
  int y = radius;
  int delta = 1 - 2 * radius;
  int error = 0;
  while (y >= 0) {
    painter.drawPoint(QPoint(x0 + x, y0 + y));
    painter.drawPoint(QPoint(x0 + x, y0 - y));
    painter.drawPoint(QPoint(x0 - x, y0 + y));
    painter.drawPoint(QPoint(x0 - x, y0 - y));
    error = 2 * (delta + y) - 1;
    if (delta < 0 && error <= 0) {
      ++x;
      delta += 2 * x + 1;
      continue;
    }
    error = 2 * (delta - x) - 1;
    if (delta > 0 && error > 0) {
      --y;
      delta += 1 - 2 * y;
      continue;
    }
    ++x;
    delta += 2 * (x - y);
    --y;
  }
}

void MainWindow::on_pushButton_clicked() {
  line = true;
  update();
}

void MainWindow::on_pushButton_2_clicked() {
  circle = true;
  update();
}
