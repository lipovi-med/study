#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>
#include <QString>

#define BIND_PORT 12345

enum MessageType {
    TYPE_TIME = 0,
    TYPE_TEXT = 1
};

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket(void);
    void SendDatagram(QByteArray data);
    void SendTextDatagram(QString text);

private slots:
    void readPendingDatagrams(void);

private:
    void processTimeDatagram(QNetworkDatagram datagram);
    void processTextDatagram(QNetworkDatagram datagram);

    QUdpSocket* serviceUdpSocket;

signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendTextToGUI(QString data, QHostAddress sender, quint16 senderPort, int size);
};

#endif // UDPWORKER_H
