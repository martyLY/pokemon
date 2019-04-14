#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QCloseEvent>
#include <QRandomGenerator>
#include <QTimer>
#include "mainpage.h"
#include "startmenu.h"
#include "signuppage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
protected:
    QUdpSocket *usrSocket;
    void closeEvent(QCloseEvent *);
private slots:
    void choosePageToProcessData();
    void setNewPage(int);
private:
    Mainpage *mainpage;
    StartMenu *startmenu;
    SignupPage *signuppage;
    QTimer *isOnline;

    Ui::MainWindow *ui;
    QStackedLayout *stackedLayout;
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
};

#endif // MAINWINDOW_H
