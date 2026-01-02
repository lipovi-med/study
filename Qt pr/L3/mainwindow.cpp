#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    con_inf_win = new ConInfWin();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete con_inf_win;
}

void MainWindow::on_pushButton_clicked()
{
    con_inf_win->show();
}

