#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    client = new TCPclient(this);

    //Доступность полей по умолчанию
    ui->le_data->setEnabled(false);
    ui->pb_request->setEnabled(false);
    ui->lb_connectStatus->setText("Отключено");
    ui->lb_connectStatus->setStyleSheet("color: red");

    // Соединяем сигналы клиента со слотами MainWindow
    connect(client, &TCPclient::sig_sendTime, this, &MainWindow::DisplayTime);
    connect(client, &TCPclient::sig_sendStat, this, &MainWindow::DisplayStat);
    connect(client, &TCPclient::sig_connectStatus, this, &MainWindow::DisplayConnectStatus);
    connect(client, &TCPclient::sig_Disconnected, this, [&]{
        ui->lb_connectStatus->setText("Отключено");
        ui->lb_connectStatus->setStyleSheet("color: red");
        ui->pb_connect->setText("Подключиться");
        ui->le_data->setEnabled(false);
        ui->pb_request->setEnabled(false);
        ui->spB_port->setEnabled(true);
        ui->spB_ip1->setEnabled(true);
        ui->spB_ip2->setEnabled(true);
        ui->spB_ip3->setEnabled(true);
        ui->spB_ip4->setEnabled(true);
        ui->tb_result->append("Отключено от сервера");
    });

    // Соединяем другие сигналы
    connect(client, &TCPclient::sig_sendFreeSize, this, &MainWindow::DisplayFreeSpace);
    connect(client, &TCPclient::sig_SendReplyForSetData, this, &MainWindow::SetDataReply);
    connect(client, &TCPclient::sig_Error, this, &MainWindow::DisplayError);
    connect(client, &TCPclient::sig_Success, this, &MainWindow::DisplaySuccess);

    // Кнопка очистки лога
    connect(ui->pb_clear, &QPushButton::clicked, ui->tb_result, &QTextBrowser::clear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayTime(QDateTime time)
{
    QString formattedTime = time.toString("dd MMM yyyy hh:mm:ss");
    ui->tb_result->append("Текущие время и дата на сервере: " + formattedTime);
}

void MainWindow::DisplayFreeSpace(uint32_t freeSpace)
{
    ui->tb_result->append("Свободное место на сервере: " + QString::number(freeSpace) + " байт");
}

void MainWindow::SetDataReply(QString replyString)
{
    ui->tb_result->append("Ответ на отправку данных: " + replyString);
}

void MainWindow::DisplayStat(StatServer stat)
{
    QString statText = QString(
                           "Статистика сервера:\n"
                           "  Принято байт: %1\n"
                           "  Передано байт: %2\n"
                           "  Принято пакетов: %3\n"
                           "  Передано пакетов: %4\n"
                           "  Время работы: %5 сек\n"
                           "  Клиентов подключено: %6"
                           ).arg(stat.incBytes)
                           .arg(stat.sendBytes)
                           .arg(stat.revPck)
                           .arg(stat.sendPck)
                           .arg(stat.workTime)
                           .arg(stat.clients);

    ui->tb_result->append(statText);
}

void MainWindow::DisplayError(uint16_t error)
{
    switch (error) {
    case ERR_NO_FREE_SPACE:
        ui->tb_result->append("Ошибка: недостаточно свободного места на сервере");
        break;
    case ERR_NO_FUNCT:
        ui->tb_result->append("Ошибка: функционал не реализован");
        break;
    default:
        ui->tb_result->append("Неизвестная ошибка: " + QString::number(error));
        break;
    }
}

void MainWindow::DisplaySuccess(uint16_t typeMess)
{
    switch (typeMess) {
    case CLEAR_DATA:
        ui->tb_result->append("Данные на сервере успешно очищены");
        break;
    default:
        ui->tb_result->append("Операция выполнена успешно");
        break;
    }
}

void MainWindow::DisplayConnectStatus(uint16_t status)
{
    if(status == ERR_CONNECT_TO_HOST){
        ui->tb_result->append("Ошибка подключения к порту: " + QString::number(ui->spB_port->value()));
    }
    else{
        ui->lb_connectStatus->setText("Подключено");
        ui->lb_connectStatus->setStyleSheet("color: green");
        ui->pb_connect->setText("Отключиться");
        ui->spB_port->setEnabled(false);
        ui->pb_request->setEnabled(true);
        ui->spB_ip1->setEnabled(false);
        ui->spB_ip2->setEnabled(false);
        ui->spB_ip3->setEnabled(false);
        ui->spB_ip4->setEnabled(false);
        ui->tb_result->append("Успешно подключено к серверу");
    }
}

void MainWindow::on_pb_connect_clicked()
{
    if(ui->pb_connect->text() == "Подключиться"){
        uint16_t port = ui->spB_port->value();
        QString ip = ui->spB_ip4->text() + "." +
                     ui->spB_ip3->text() + "." +
                     ui->spB_ip2->text() + "." +
                     ui->spB_ip1->text();

        ui->tb_result->append("Подключение к " + ip + ":" + QString::number(port));
        client->ConnectToHost(QHostAddress(ip), port);
    }
    else{
        ui->tb_result->append("Отключение от сервера...");
        client->DisconnectFromHost();
    }
}

void MainWindow::on_pb_request_clicked()
{
    ServiceHeader header;
    header.id = ID;
    header.status = STATUS_SUCCES;

    switch (ui->cb_request->currentIndex()){
    case 0: // Получить время
        header.idData = GET_TIME;
        header.len = 0;
        ui->tb_result->append("Запрос времени...");
        break;
    case 1: // Получить свободное место
        header.idData = GET_SIZE;
        header.len = 0;
        ui->tb_result->append("Запрос свободного места...");
        break;
    case 2: // Получить статистику
        header.idData = GET_STAT;
        header.len = 0;
        ui->tb_result->append("Запрос статистики...");
        break;
    case 3: // Отправить данные
        if(ui->le_data->text().isEmpty()){
            ui->tb_result->append("Ошибка: поле данных пустое");
            return;
        }
        header.idData = SET_DATA;
        client->SendData(header, ui->le_data->text());
        ui->tb_result->append("Отправка данных...");
        return;
    case 4: // Очистить память на сервере
        header.idData = CLEAR_DATA;
        header.len = 0;
        ui->tb_result->append("Запрос очистки данных...");
        break;
    default:
        ui->tb_result->append("Такой запрос не реализован в текущей версии");
        return;
    }

    client->SendRequest(header);
}

void MainWindow::on_cb_request_currentIndexChanged(int index)
{
    if(index == 3){
        ui->le_data->setEnabled(true);
    }
    else{
        ui->le_data->setEnabled(false);
    }
}
