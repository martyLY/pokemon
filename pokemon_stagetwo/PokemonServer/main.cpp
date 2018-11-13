#include <QCoreApplication>

#include "udpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UdpServer *server = new UdpServer();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("pokemontest");
    db.setUserName("root");
    db.setPassword("mashiro7221");
    db.open();
    QSqlQuery query(db);
    qDebug()<<query.exec("SELECT COLUMN_JSON(pokemoninfo) from pokemoninfo where uid = 0;");
    qDebug()<<query.lastError();
    while(query.next()) {
        qDebug()<<QJsonDocument::fromJson(query.value("COLUMN_JSON(pokemoninfo)").toByteArray())["name"].toString();
    }
    return a.exec();
}
