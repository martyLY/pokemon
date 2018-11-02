#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QObject>
#include <QWidget>

namespace Ui {
    class Mainpage;
}

class Mainpage : public QWidget
{
    Q_OBJECT
public:
   explicit  Mainpage(QWidget *parent = nullptr);
    virtual ~Mainpage();

private:
    Ui::Mainpage *mainpageUi;
};

#endif // MAINPAGE_H
