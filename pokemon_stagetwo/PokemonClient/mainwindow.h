#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "global.h"
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
    QUdpSocket *user;

private slots:

private:
    Mainpage *mainpage;
    StartMenu *startmenu;
    SignupPage *signuppage;

    Ui::MainWindow *ui;
    QStackedLayout *stackedLayout;
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
};

#endif // MAINWINDOW_H
