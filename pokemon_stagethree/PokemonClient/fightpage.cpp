#include "fightpage.h"
#include "ui_fightpage.h"

Fightpage::Fightpage(Usr* _usr,QWidget *parent) :
    usr(_usr),

    mainWindowPtr(parent),
    ui(new Ui::Fightpage)
{
    setWindowFlags(Qt::WindowMinMaxButtonsHint|Qt::WindowFullscreenButtonHint);
                                                            //设置只有放大和缩小按钮
    ui->setupUi(this);
}

Fightpage::~Fightpage()
{
    delete ui;
}

void Fightpage::on_pushButton_clicked()
{
    this->close();
}

void Fightpage::prepare(QNetworkDatagram n) {
    /*记录对方地址*/
    fightSocket = new QUdpSocket();
    connect(fightSocket, SIGNAL(readyRead()), this, SLOT(dataRecv()), Qt::DirectConnection);

    fightCoreAddr = n.senderAddress();
    fightCorePort = static_cast<quint16>(n.senderPort());

    /*设置界面属性*/
    QJsonDocument data = QJsonDocument::fromJson(n.data());

    fightType = data["fighttype"].toInt();
    /*红色方*/
    ui->redNickname->setText(data["rednickname"].toString());
    QJsonObject redPokemoninfo = data["redpokemoninfo"].toObject();
    ui->redPokemonName->setText(redPokemoninfo["name"].toString());
    ui->redBaseAttack->setNum(redPokemoninfo["base_attack"].toInt());
    ui->redDefense->setNum(redPokemoninfo["defense_power"].toInt());
    ui->redLevel->setNum(redPokemoninfo["level"].toInt());
    ui->redWsp->setNum(redPokemoninfo["wsp"].toDouble());
    ui->redRace->setText(RACE[redPokemoninfo["race"].toInt()]);
    ui->redRarity->setText(RARITY[redPokemoninfo["rarity"].toInt()]);
    ui->redHp->setRange(0, redPokemoninfo["max_hp"].toInt());
    ui->redHp->setValue(redPokemoninfo["max_hp"].toInt());

    /*蓝色方*/
    ui->blueNickname->setText(data["bluenickname"].toString());
    QJsonObject bluePokemoninfo = data["bluepokemoninfo"].toObject();
    ui->bluePokemonName->setText(bluePokemoninfo["name"].toString());
    ui->blueBaseAttack->setNum(bluePokemoninfo["base_attack"].toInt());
    ui->blueDefense->setNum(bluePokemoninfo["defense_power"].toInt());
    ui->blueLevel->setNum(bluePokemoninfo["level"].toInt());
    ui->blueWsp->setNum(bluePokemoninfo["wsp"].toDouble());
    ui->blueRace->setText(RACE[bluePokemoninfo["race"].toInt()]);
    ui->blueRarity->setText(RARITY[bluePokemoninfo["rarity"].toInt()]);
    ui->blueHp->setRange(0, bluePokemoninfo["max_hp"].toInt());
    ui->blueHp->setValue(bluePokemoninfo["max_hp"].toInt());

    QJsonObject reply;
    reply.insert("DataType", datatype::fightaddr);
    fightSocket->writeDatagram(QJsonDocument(reply).toJson(),
                                   fightCoreAddr, fightCorePort);

}

void Fightpage::dataRecv() {
    while(fightSocket->hasPendingDatagrams()) {
        readPendingDatagram(QJsonDocument::fromJson(fightSocket->receiveDatagram().data()));
    }
}

void Fightpage::readPendingDatagram(QJsonDocument data) {
    qDebug()<<data;
    if(data["DataType"] == datatype::redattack) {
        //红色方攻击
        DamageInfo damageinfo;  //伤害信息
        damageinfo.setDamageInfo(data["damageinfo"].toObject());
        ui->blueHp->setValue(ui->blueHp->value()-static_cast<int>(damageinfo.damage));
                                                                    //蓝色方hp减少
        //输出详细的战斗信息
        QString bluefightinfo;
        if(damageinfo.damageType == DamageType::miss) {
            bluefightinfo.append("red's attack miss!!\n");
        }
        else if(damageinfo.damageType == DamageType::ultimateskill ) {
            bluefightinfo.append("blue is attacked by ultimateskill, damage value: "
                                      + QString::number(damageinfo.damage)+'\n');
        }
        else if(damageinfo.damageType == DamageType::baseAttack ) {
            //是否产生暴击
            if(damageinfo.isCritical) {
                bluefightinfo.append("blue is attacked critically, ");
            }
            else {
                bluefightinfo.append("blue is attacked normally, ");
            }
            bluefightinfo.append(QString::number(damageinfo.damage) + '\n');
            bluefightinfo.append("+++++one attack++++++\n");
            ui->bluefightinfo->append(bluefightinfo); //显示战斗数据
        }
        this->update();
    }
    else if(data["DataType"] == datatype::blueattack) {
        //蓝色方攻击
        DamageInfo damageinfo;
        damageinfo.setDamageInfo(data["damageinfo"].toObject());
        ui->redHp->setValue(ui->redHp->value()-static_cast<int>(damageinfo.damage));
                                                                //红色方血量减少
        //输出详细的战斗信息
        QString redfightinfo;
        if(damageinfo.damageType == DamageType::miss) {
            redfightinfo.append("blue's attack miss!!\n");
        }
        else if(damageinfo.damageType == DamageType::ultimateskill ) {
            redfightinfo.append("red is attacked by ultimateskill, damage value: "
                                    + QString::number(damageinfo.damage)+'\n');
        }
        else if(damageinfo.damageType == DamageType::baseAttack ) {
            //是否产生暴击
            if(damageinfo.isCritical) {
                redfightinfo.append("red is attacked critically, ");
            }
            else {
                redfightinfo.append("red is attacked normally, ");
            }
            redfightinfo.append(QString::number(damageinfo.damage) + '\n');
            redfightinfo.append("+++++one attack++++++\n");
            ui->redfightinfo->append(redfightinfo);
        }
        this->update();
    }
    else if(data["DataType"] == datatype::win ) {
        ui->redfightinfo->append("win!!!!!!");
        ui->bluefightinfo->append("win!!!!!");

        //弹出结果窗口
        QMessageBox *resultinfo = new QMessageBox();
        resultinfo->setWindowFlags(Qt::CustomizeWindowHint|Qt::SubWindow);
        resultinfo->setText("You Win:)");
        resultinfo->setStandardButtons(QMessageBox::Ok);
        int result = resultinfo->exec(); //无限循环等待用户点击
        if(result == QMessageBox::Ok) {
            mainWindowPtr->show();
            close();
        }
    }
    else if(data["DataType"] == datatype::lose) {
        ui->redfightinfo->append("lose!!!!!!");
        ui->bluefightinfo->append("lose!!!!!");

        //弹出结果窗口
        QMessageBox *resultinfo = new QMessageBox();
        resultinfo->setWindowFlags(Qt::CustomizeWindowHint|Qt::SubWindow);
        resultinfo->setText("You Lose:(");
        resultinfo->setStandardButtons(QMessageBox::Ok);
        int result = resultinfo->exec();  //无限循环等待用户点击
        if(result == QMessageBox::Ok) {

            //模式为死斗, 并且为败者, 选择送出宠物
            if(fightType == DEADFIGHT) {
                sendChoosedPokemon();
            }

            mainWindowPtr->show();
            close();
        }
    }
}

void Fightpage::sendChoosedPokemon(){
    QStringList nameList = usr->getSomePokemonName();  //随机选择一些精灵展示
    pokemonChoose choosePage;

    //显示设置
    for(int i = 0; i < nameList.size(); i++) {
        choosePage.setItemText(nameList.at(i));
    }

    QString choosedPokemon = choosePage.exac(); //无限循环,等待返回选择精灵信息

    //发送结果
    QJsonObject data;
    data.insert("DataType", datatype::losepokemon);
    data.insert("pokemonname", choosedPokemon);

    fightSocket->writeDatagram(QJsonDocument(data).toJson(),
                               fightCoreAddr, fightCorePort);
}
