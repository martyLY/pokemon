#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include "global.h"
namespace Ui {
    class StartMenu;
}
class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget*parent = nullptr);
    ~StartMenu();
protected:
    QUdpSocket *user;
private:
    void initSocket();
    void readPendingDatagram();
//    QHostAddress serverAddr;
//    quint16 port;
private:
    Ui::StartMenu *startmenuUi;
signals:
    void switchPage(int i);
public slots:
private slots:
    void on_loginButton_clicked();
    void on_signupButton_clicked();
};

#endif // STARTMENU_H
