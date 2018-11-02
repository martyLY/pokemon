#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QWidget>

namespace Ui {
    class SignupPage;
}
class SignupPage : public QWidget
{
    Q_OBJECT
public:
    explicit SignupPage(QWidget *parent = nullptr);

private:
    Ui::SignupPage *signuppageUi;
signals:

public slots:
};

#endif // SIGNUPPAGE_H
