#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QWidget>

namespace Ui {
class PlayerInfo;
}

class PlayerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInfo(QWidget *parent = nullptr);
    ~PlayerInfo();

private:
    Ui::PlayerInfo *ui;
};

#endif // PLAYERINFO_H
