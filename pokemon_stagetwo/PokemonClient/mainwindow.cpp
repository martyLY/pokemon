#include "mainwindow.h"
#include "ui_mainwindow.h"

QHostAddress serverAddr(QHostAddress::LocalHost);
quint16 port = 2333;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    usrSocket = new  QUdpSocket();    
    quint16 port = static_cast<quint16>(QRandomGenerator::global()->bounded(65535));
    this->usrSocket->bind(port);

    mainpage = new Mainpage(usrSocket);
    startmenu = new StartMenu(usrSocket);
    signuppage = new SignupPage(usrSocket);

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
    connect(signuppage, SIGNAL(switchPage(int)), stackedLayout, SLOT(setCurrentIndex(int)));
    connect(startmenu, SIGNAL(setOnlineUsrList(QJsonDocument)), mainpage, SLOT(setOtherUsrInfo(QJsonDocument)));
    connect(startmenu, SIGNAL(setUsr(QJsonDocument)), mainpage, SLOT(setClientUsr(QJsonDocument)));
    connect(usrSocket, SIGNAL(readyRead()), this, SLOT(choosePageToProcessData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(stackedLayout->currentIndex() == 2) {
        //如果是主界面关闭, 需要通知服务端
        mainpage->close();
    }
    else if(stackedLayout->currentIndex() == 3) {
        //to do
    }
    event->accept();
}

void MainWindow::choosePageToProcessData() {
    //根据当前显示的页面是哪个 来决定执行哪个页面的dataRecv函数
    //qDebug()<<"currentindex:"<<stackedLayout->currentIndex()<<endl;
    switch (stackedLayout->currentIndex()) {
    case 0: startmenu->dataRecv(); break;
    case 1: signuppage->dataRecv(); break;
    case 2: mainpage->dataRecv(); break;
    default: break;
    }
}

//void MainWindow::choosePageToProcessData()
//{

//    QNetworkDatagram datagram;
//    while(usrSocket->hasPendingDatagrams())
//        datagram = usrSocket->receiveDatagram();
//    QJsonDocument dataJson = QJsonDocument::fromJson(datagram.data());
//    qDebug()<<dataJson<<endl;
//    switch (dataJson["DataType"].toInt()) {
//    case datatype::loginno: startmenu->readPendingDatagram(datagram); break;
//    case datatype::loginyes: startmenu->readPendingDatagram(datagram); break;

//    case datatype::signupno: signuppage->readPendingDatagram(datagram); break;
//    case datatype::signupyes: signuppage->readPendingDatagram(datagram); break;
//    case datatype::signuprepeat: signuppage->readPendingDatagram(datagram); break;

//    case datatype::onlineusradd: mainpage->readPendingDatagram(datagram); break;
//    case datatype::onlineusrerase: mainpage->readPendingDatagram(datagram); break;
//    case datatype::close: mainpage->readPendingDatagram(datagram); break;

//    default: break;
//    }
//}



