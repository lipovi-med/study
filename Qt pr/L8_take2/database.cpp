#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();  //Объект низкого уровня, в которм настраивается подключение к БД

    query_model = new QSqlQueryModel(this); //Создание класса запроса в таблицу

    table_ = new QSqlTableModel(this);  //Созник класса для ответа

}

DataBase::~DataBase()
{
    delete dataBase;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{
   // dataBase->database();
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request)
{

    if (!request.contains("WHERE", Qt::CaseInsensitive)) {

        table_->setTable("film");
        table_->select();

        table_->setHeaderData(0, Qt::Horizontal, "Название фильма");
        table_->setHeaderData(1, Qt::Horizontal, "Описание фильма");

        emit sig_SendDataFromDB(table_);
    }
    else {
        query_model->setQuery(request);

        if (query_model->lastError().isValid()) {
            qDebug() << query_model->lastError().text();
        }

        // FIX: заголовки столбцов
        query_model->setHeaderData(0, Qt::Horizontal, "Название фильма");
        query_model->setHeaderData(1, Qt::Horizontal, "Описание фильма");

        emit sig_SendDataFromDB(query_model);
    }
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
