#include "coninfwin.h"
#include "ui_coninfwin.h"

ConInfWin::ConInfWin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConInfWin)
{
    ui->setupUi(this);
}

ConInfWin::~ConInfWin()
{
    delete ui;
}
