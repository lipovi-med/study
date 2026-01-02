#include <QCoreApplication>
#include <QtSql>
#include <QtNetwork>
#include <QDnsMailExchangeRecord>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDnsMailExchangeRecord rec;
    qDebug() << rec.name();

    QSqlDatabase db;
    qDebug() << db.isValid();

    return a.exec();
}
