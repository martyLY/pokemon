#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->startMenu->setVisible(true);
    ui->signupMenu->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_logininButton_clicked()
{
    //to do
    //将数据传给服务器,确定账号密码是否正确
}

void MainWindow::on_signupButton_clicked()
{
    ui->startMenu->setVisible(false);
    ui->signupMenu->setVisible(true);
}

void MainWindow::on_check_clicked()
{
    //to do
    //数据传给服务器,生成一个账户,并进入主页面
}
