#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//Задание груп бокса
    ui->gb_radio->setTitle("Время суток");

    ui->rb_1->setText("День");
    ui->rb_1->setChecked(true);

    ui->rb_2->setText("Ночь");

//Задание прогресс бара и кнопки
    ui->label->setText("Установка погоды");

    ui->pBar->setMaximum(10);
    ui->pBar->setMinimum(0);
    ui->pBar->setValue(0);
    ui->pBar->setFormat("%p%");

    ui->pb_->setText("Установить");
//Задание комбобокса


   ui->cB_->addItem("Холодно");
   ui->cB_->addItem("Жарко");
   ui->cB_->addItem("Дождь");
   ui->cB_->addItem("Засуха");
   ui->cB_->addItem("Ураган");
   ui->cB_->addItem("Штиль");
   ui->cB_->setCurrentIndex(-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb__clicked()
{
    int counter = ui->pBar->value();
    if(counter < 10){ui->pBar->setValue(++counter);}
    else{ui->pBar->setValue(0);};
}

