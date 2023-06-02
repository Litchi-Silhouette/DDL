#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "windowbase.h"
#include <QGraphicsEffect>
#include "set_help_acc.h"
#include "Game.hpp"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public windowBase
{
    Q_OBJECT

public:
    explicit MenuWindow(Game& game, QWidget *parent = nullptr);
    ~MenuWindow();
    void updateBtn();
protected:
    void showEvent(QShowEvent*);
private slots:
    void on_helpBtn_clicked();

    void on_setBtn_clicked();

    void on_exitBtn_clicked();
    void on_level1Btn_clicked();

    void on_level2Btn_clicked();

    void on_level3Btn_clicked();

private:
    void setBlur(int extent);

    Ui::MenuWindow *ui;
    SetDialog* setDlg;
    HelpDialog* helpDlg;
    QGraphicsBlurEffect* blureffect = new QGraphicsBlurEffect;
    Game& statics;
};

#endif // MENUWINDOW_H
