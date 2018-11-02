#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainpage = new Mainpage;
    startmenu = new StartMenu;
    signuppage = new SignupPage;
    stackedLayout = new QStackedLayout();
    mainLayout = new QVBoxLayout();

    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);


    stackedLayout->addWidget(startmenu);
    stackedLayout->addWidget(signuppage);
    stackedLayout->addWidget(mainpage);

    mainLayout->addLayout(stackedLayout);
    stackedLayout->setCurrentIndex(0);
    centralWidget()->setLayout(mainLayout);
    connect(startmenu, SIGNAL(switchPage(int)), stackedLayout, SLOT(setCurrentIndex(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::initSocket() {
//    //userSend = new QUdpSocket;
//    user = new QUdpSocket;
//    serverAddr.setAddress(QHostAddress::LocalHost);
//    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    serverPort = 2333;
//}
//void MainWindow::on_logininButton_clicked()
//{
//    //to do
//    //将数据传给服务器,确定账号密码是否正确
//    QJsonObject loginData;
//    loginData.insert("DataType", datatype::loginin);
//    loginData.insert("name", ui->loginName->text());
//    loginData.insert("password", ui->loginPassword->text());
//    /* to do
//     * 1.缺少字符串格式判断
//     * 2.缺少加密
//     */
//    QJsonDocument loginDataToSend(loginData);
//    if(user->writeDatagram(loginDataToSend.toJson(), serverAddr, serverPort)
//            < loginDataToSend.toJson().length()) {

//        //消息没有传送完, 报错
//        qDebug()<<"Network errer, no send,please try again!"<<endl;
//    }
//    else {
//        //传输成功
//        if(user->waitForReadyRead(600)) {
//            //返回true,没有超时
//            readPendingDatagram();
//        }
//        else {
//            qDebug()<<"Network errer, no reply, please try again!"<<endl;
//        }
//    }
//}

//void MainWindow::readPendingDatagram() {
//    QJsonDocument dataReceive;
//    QByteArray data;
//    data.resize(user->pendingDatagramSize());
//    user->readDatagram(data.data(), data.size());
//    dataReceive.fromJson(data);
//    if(dataReceive["DataType"] == datatype::loginin) {
//        /*登录成功
//         * to do 切换页面
//         * 载入用户信息
//         */
//    }
//}

