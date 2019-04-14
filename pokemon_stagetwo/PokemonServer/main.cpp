#include <QCoreApplication>

#include "udpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UdpServer *server = new UdpServer();

//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("127.0.0.1");
//    db.setDatabaseName("pokemontest");
//    db.setUserName("mashiro");
//    db.setPassword("mashiro7221!");
//    db.open();
//    QSqlQuery query(db);
//    //query.prepare("select * from pokemoninfo");
//    QJsonObject object;
//    object.insert("wo","mashior");
//    object.insert("ni","ruanmori");
//    QJsonDocument doc(object);
//    query.prepare("insert into pokemoninfo values "
//                  "(7389, :data);");
//    qDebug()<<doc.toJson();
//    query.bindValue(":data", doc.toJson());
//    qDebug()<<query.exec();

//    query.prepare("select pokemoninfo from pokemoninfo where uid = 7389;");
//    query.exec();
//    while(query.next())
//        qDebug()<<query.lastError()<<endl<<QJsonDocument::fromJson(query.value(0).toByteArray())["ni"];
    return a.exec();
}
