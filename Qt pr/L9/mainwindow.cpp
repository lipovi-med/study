#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendTextToGUI, this, &MainWindow::DisplayText);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{
        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);
        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}

void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                           "Принято пакетов " + QString::number(counterPck));
}

void MainWindow::DisplayText(QString data, QHostAddress sender, quint16 senderPort, int size)
{
    QString message = QString("Принято сообщение от %1, размер сообщения(байт) %2")
                          .arg(sender.toString())
                          .arg(size);

    ui->te_result->append(message);
}

void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}

void MainWindow::on_pb_sendText_clicked()
{
    QString text = ui->le_textToSend->text();
    if (!text.isEmpty()) {
        udpWorker->SendTextDatagram(text);
        ui->le_textToSend->clear();
    }
}
