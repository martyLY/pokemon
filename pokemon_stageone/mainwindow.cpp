#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //qDebug()<<test.getAllAttritubeInfo().toStdString().data()<<endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generate_pokemon_clicked()
{
    test = new Ashe("mashiro");
    ui->infoShow->setText(test->getAllAttritubeInfo());
}



void MainWindow::on_getExp_clicked()
{
    test->expUp(50);
    ui->infoShow->setText(test->getAllAttritubeInfo());
}
