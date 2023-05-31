#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include "set_help_acc_start.h"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_helpBtn_clicked();

    void on_setBtn_clicked();

    void on_exitBtn_clicked();
signals:
    void changeWindow(int index);
private:
    void setBlur(int extent);

    Ui::MenuWindow *ui;
    SetDialog* setDlg;
    HelpDialog* helpDlg;
    QGraphicsBlurEffect* blureffect = new QGraphicsBlurEffect;
};

#endif // MENUWINDOW_H
