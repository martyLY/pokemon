#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonValue>
#include <QTime>

#include "global.h"
namespace Ui {
    class SignupPage;
}
class SignupPage : public QWidget
{
    Q_OBJECT
public:
    explicit SignupPage(QWidget *parent = nullptr);

private:
    QUdpSocket *user;
    void initSocket();
    void readPendingDatagram();
    Ui::SignupPage *signuppageUi;
signals:
    void switchPage(int);
public slots:
private slots:
    void on_generatePokemon_clicked();
};

#endif // SIGNUPPAGE_H
