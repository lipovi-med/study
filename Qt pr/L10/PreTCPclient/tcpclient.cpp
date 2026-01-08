#include "tcpclient.h"

/* ServiceHeader
 * Для работы с потоками наши данные необходимо сериализовать.
 * Поскольку типы данных не стандартные перегрузим оператор << Для работы с ServiceHeader
*/
QDataStream &operator >>(QDataStream &out, ServiceHeader &data){
    out >> data.id;
    out >> data.idData;
    out >> data.status;
    out >> data.len;
    return out;
};

QDataStream &operator <<(QDataStream &in, const ServiceHeader &data){
    in << data.id;
    in << data.idData;
    in << data.status;
    in << data.len;
    return in;
};

/* StatServer
 * Перегружаем операторы для работы со статистикой
*/
QDataStream &operator >>(QDataStream &out, StatServer &data){
    out >> data.incBytes;
    out >> data.sendBytes;
    out >> data.revPck;
    out >> data.sendPck;
    out >> data.workTime;
    out >> data.clients;
    return out;
};

QDataStream &operator <<(QDataStream &in, const StatServer &data){
    in << data.incBytes;
    in << data.sendBytes;
    in << data.revPck;
    in << data.sendPck;
    in << data.workTime;
    in << data.clients;
    return in;
};

/*
 * Поскольку мы являемся клиентом, инициализацию сокета
 * проведем в конструкторе. Также необходимо соединить
 * сокет со всеми необходимыми нам сигналами.
*/
TCPclient::TCPclient(QObject *parent) : QObject(parent), socket(nullptr)
{
    socket = new QTcpSocket(this);

    // Соединяем сигналы сокета с нашими слотами
    connect(socket, &QTcpSocket::readyRead, this, &TCPclient::ReadyReed);
    connect(socket, &QTcpSocket::disconnected, this, [=]{
        emit sig_Disconnected();
    });
    connect(socket, &QTcpSocket::connected, this, [=]{
        emit sig_connectStatus(STATUS_SUCCES);
    });
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, [=](QAbstractSocket::SocketError error){
                Q_UNUSED(error);
                emit sig_connectStatus(ERR_CONNECT_TO_HOST);
            });
}

/* write
 * Метод отправляет запрос на сервер. Сериализировать будем
 * при помощи QDataStream
*/
void TCPclient::SendRequest(ServiceHeader head)
{
    if(!socket || socket->state() != QAbstractSocket::ConnectedState)
        return;

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    head.status = TYPE_REQ;
    out << head;

    socket->write(data);
}

/* write
 * Такой же метод только передаем еще данные.
*/
void TCPclient::SendData(ServiceHeader head, QString str)
{
    if(!socket || socket->state() != QAbstractSocket::ConnectedState)
        return;

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);

    head.status = TYPE_REQ;
    head.len = static_cast<uint32_t>(str.toUtf8().size());
    out << head;
    out.writeRawData(str.toUtf8().constData(), static_cast<int>(str.toUtf8().size()));

    socket->write(data);
}

/*
 * \brief Метод подключения к серверу
 */
void TCPclient::ConnectToHost(QHostAddress host, uint16_t port)
{
    if(socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
    socket->connectToHost(host, port);
}

/*
 * \brief Метод отключения от сервера
 */
void TCPclient::DisconnectFromHost()
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->disconnectFromHost();
}

void TCPclient::ReadyReed()
{
    if(!socket) return;

    QDataStream incStream(socket);
    incStream.setVersion(QDataStream::Qt_6_0);

    if(incStream.status() != QDataStream::Ok){
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setText("Ошибка открытия входящего потока для чтения данных!");
        msg.exec();
        return;
    }

    //Читаем до конца потока
    while(!incStream.atEnd()){
        //Если мы обработали предыдущий пакет, мы скинули значение idData в 0
        if(servHeader.idData == 0){
            //Проверяем количество полученных байт
            if(socket->bytesAvailable() < static_cast<qint64>(sizeof(ServiceHeader))){
                return;
            }
            else{
                //Читаем заголовок
                incStream >> servHeader;
                //Проверяем на корректность данных
                if(servHeader.id != ID){
                    uint16_t hdr = 0;
                    while(!incStream.atEnd()){
                        incStream >> hdr;
                        if(hdr == ID){
                            incStream >> servHeader.idData;
                            incStream >> servHeader.status;
                            incStream >> servHeader.len;
                            break;
                        }
                    }
                }
            }
        }
        //Если получены не все данные, ждем новую посылку
        if(socket->bytesAvailable() < static_cast<qint64>(servHeader.len)){
            return;
        }
        else{
            //Обработка данных
            ProcessingData(servHeader, incStream);
            servHeader.idData = 0;
            servHeader.status = 0;
            servHeader.len = 0;
        }
    }
}

void TCPclient::ProcessingData(ServiceHeader header, QDataStream &stream)
{
    switch (header.idData){
    case GET_TIME: {
        uint32_t timeValue;
        stream >> timeValue;
        QDateTime time = QDateTime::fromSecsSinceEpoch(timeValue);
        emit sig_sendTime(time);
        break;
    }
    case GET_SIZE: {
        uint32_t freeSpace;
        stream >> freeSpace;
        emit sig_sendFreeSize(freeSpace);
        break;
    }
    case GET_STAT: {
        StatServer stat;
        stream >> stat.incBytes;
        stream >> stat.sendBytes;
        stream >> stat.revPck;
        stream >> stat.sendPck;
        stream >> stat.workTime;
        stream >> stat.clients;
        emit sig_sendStat(stat);
        break;
    }
    case SET_DATA: {
        QString reply;
        stream >> reply;
        emit sig_SendReplyForSetData(reply);
        break;
    }
    case CLEAR_DATA: {
        emit sig_Success(CLEAR_DATA);
        break;
    }
    default:
        emit sig_Error(ERR_NO_FUNCT);
        break;
    }
}
