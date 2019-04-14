#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generate_pokemon_clicked()
{
    int whatisrace = QRandomGenerator::global()->bounded(3);
    switch (whatisrace) {
    case 0: test = new Ashe("mashiro"); break;
    case 1: test = new Anne("mahsiro"); break;
    case 2: test = new Vladimir("mashiro"); break;
    default: break;
    }
    ui->infoShow->setText(test->getAllAttritubeInfo());
}

void MainWindow::on_getExp_clicked()
{
    test->expUp(50);
    ui->infoShow->setText(test->getAllAttritubeInfo());
}

void MainWindow::on_pushButton_clicked()
{
    if(test == nullptr) return;
    QString attackinfo;
    QPair<unsigned int, BaseSkill> info = test->attack();
    qDebug()<<"errre";
    attackinfo.append("damage: "+ QString::number(info.first));
    attackinfo.append("\ntype: "+BASESKILL[info.second]);

    ui->attackinfo->setText(attackinfo);
}
