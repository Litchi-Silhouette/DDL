#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QGraphicsEffect>
#include "set_help_acc_start.h"
#include "../Game.hpp"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(Game& game, QWidget *parent = nullptr);
    ~MenuWindow();
    void updateBtn();
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
    Game& statics;
};

#endif // MENUWINDOW_H
