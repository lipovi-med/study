#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{
    serviceUdpSocket = new QUdpSocket(this);
}

void UDPworker::InitSocket()
{
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обработчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::AnyIPv4, BIND_PORT);

    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);
}

void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

void UDPworker::SendTextDatagram(QString text)
{
    /*
     *  Отправляем текстовые данные на localhost и задефайненный порт
     */
    QByteArray data = text.toUtf8();
    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

void UDPworker::readPendingDatagrams(void)
{
    /*
     *  Производим чтение принятых датаграмм
     */
    while(serviceUdpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();

        // Пытаемся определить тип сообщения
        QByteArray data = datagram.data();
        QDataStream inStr(&data, QIODevice::ReadOnly);

        // Проверяем, можно ли прочитать как QDateTime
        QDateTime dateTime;
        inStr >> dateTime;

        // Сбрасываем позицию потока
        inStr.device()->seek(0);

        if (dateTime.isValid() && inStr.status() == QDataStream::Ok) {
            // Это сообщение с временем
            processTimeDatagram(datagram);
        } else {
            // Это текстовое сообщение
            processTextDatagram(datagram);
        }
    }
}

void UDPworker::processTimeDatagram(QNetworkDatagram datagram)
{
    QByteArray data = datagram.data();
    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;

    inStr >> dateTime;

    if (dateTime.isValid() && inStr.status() == QDataStream::Ok) {
        emit sig_sendTimeToGUI(dateTime);
    }
}

void UDPworker::processTextDatagram(QNetworkDatagram datagram)
{
    QByteArray data = datagram.data();
    QString text = QString::fromUtf8(data);

    emit sig_sendTextToGUI(text, datagram.senderAddress(), datagram.senderPort(), data.size());
}
