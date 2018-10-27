#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_logininButton_clicked();

    void on_signupButton_clicked();

    void on_check_clicked();

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
