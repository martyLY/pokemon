#ifndef POKEMONCHOOSE_H
#define POKEMONCHOOSE_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QLabel>
#include <QJsonObject>
#include <QListWidget>
#include <QListWidgetItem>
#include <QEventLoop>
#include <QCloseEvent>

namespace Ui {
class pokemonChoose;
}

//精灵选择类, 提供界面供用户选择精灵
//传入参数为精灵名字的列表
class pokemonChoose : public QWidget
{
    Q_OBJECT
public:
    //构造函数, 参数为精灵的名字列表
    explicit pokemonChoose(QJsonValue, QWidget *parent = nullptr);
    //构造函数, 参数为空则从用户的精灵中随机选择几个精灵
    pokemonChoose(QWidget *parent = nullptr);
    ~pokemonChoose();

    //无限循环事件执行函数, 用于等待用户选择精灵
    QString exac();

    //设置显示的精灵名字, 参数为精灵名字
    void setItemText(QString);

    //窗口关闭事件, 结束无限循环事件
    void closeEvent(QCloseEvent* );
private:
    QString choosedPokemonName;  //被选择的精灵名字
    QEventLoop *loop;  //无限循环事件

    Ui::pokemonChoose *ui;
signals:
    //发送包含被选择的精灵名字的信号
    void choosedPokemon(QString);
private slots:
    //获得被选择的item
    void pokemonHasChoosed(QListWidgetItem* );

    //在为死斗情况下的选择
    void deadFightChoosedPokemon(QListWidgetItem*);
};

#endif // POKEMONCHOOSE_H
