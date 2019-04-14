#include "pokemonchoose.h"
#include "ui_pokemonchoose.h"

pokemonChoose::pokemonChoose(QJsonValue info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pokemonChoose)
{
    //战斗开始前的精灵选择
    loop = nullptr;  //不需要无限循环事件
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint);
    move(200, 150);
    ui->pokemonToChoose->setViewMode(QListView::IconMode);

    //将精灵名字依次展示
    QJsonArray pokemonInfoList = info.toArray();
    QJsonArray::iterator iter;
    for(iter = pokemonInfoList.begin(); iter != pokemonInfoList.end(); iter++ ) {
        QListWidgetItem *item = new QListWidgetItem((*iter).toObject()["name"].toString());
        ui->pokemonToChoose->addItem(item);
    }

    //双击选择精灵后的信号链接
    connect(ui->pokemonToChoose, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(pokemonHasChoosed(QListWidgetItem* )));
}

pokemonChoose::pokemonChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pokemonChoose)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint);
    ui->pokemonToChoose->setViewMode(QListView::IconMode);

    connect(ui->pokemonToChoose, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(deadFightChoosedPokemon(QListWidgetItem* )));
}

pokemonChoose::~pokemonChoose()
{
    delete ui;
}

void pokemonChoose::pokemonHasChoosed(QListWidgetItem* item) {
    emit choosedPokemon(item->text());  //发送被选择的精灵名字
    this->close();
}

QString pokemonChoose::exac() {
    show();
    loop = new QEventLoop(this);
    loop->exec();  //无限循环

    return choosedPokemonName;  //循环结束后返回被选择的名字
}

void pokemonChoose::deadFightChoosedPokemon(QListWidgetItem* item ) {
    choosedPokemonName = item->text();
    close();
}

void pokemonChoose::setItemText(QString name) {
    QListWidgetItem *item = new QListWidgetItem(name);
    ui->pokemonToChoose->addItem(item);
}

void pokemonChoose::closeEvent(QCloseEvent *event) {
    if(loop != nullptr) {
        loop->exit(); //退出循环
    }
    event->accept();  //窗口关闭
}

