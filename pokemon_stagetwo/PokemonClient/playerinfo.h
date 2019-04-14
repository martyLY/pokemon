#ifndef PLAYINFO_H
#define PLAYINFO_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextBrowser>
#include <QString>
#include <QDebug>

namespace Ui {
class PlayerInfo;
class PlayerInfoDetail;
}

class PlayerInfoDetail;

//玩家信息类存储玩家的uid和昵称,
//和玩家的详细信息,用于在当前在线用户列表中进行显示
//需要将此类添加到qlistwidgetitem中
//example:
//  QListWidgetItem item;
//  PlayInfo info(playinfo);
//  item.additem(info);
class PlayerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInfo(QJsonDocument playinfo, QWidget *parent = nullptr);
    ~PlayerInfo();
    //显示玩家详细信息, 会调用playinfodetail类
    void showDetail();

    //获得此在线玩家的uid
    int getUid(){return uid; }
private:
    int uid;  //此在线玩家的uid

    PlayerInfoDetail *detail;  //存储详细玩家信息

    Ui::PlayerInfo *ui;
};


//玩家详细信息类,实际上会新建一个窗口
//显示玩家的详细信息,包括基本信息,和每个精灵的所有属性信息
//只能被playinfo类调用
class PlayerInfoDetail : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerInfoDetail(QJsonDocument playinfodetail, QWidget *parent = nullptr);
    ~PlayerInfoDetail();

private:
    Ui::PlayerInfoDetail *ui;
};

#endif // PLAYINFO_H
