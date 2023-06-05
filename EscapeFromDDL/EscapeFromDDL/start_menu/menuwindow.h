#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "../windowbase.h"
#include <QGraphicsEffect>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "set_help_acc.h"
#include "../Game.hpp"

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
    void hideEvent(QHideEvent*);
private slots:
    void on_helpBtn_clicked();

    void on_setBtn_clicked();

    void on_exitBtn_clicked();
    void on_level1Btn_clicked();

    void on_level2Btn_clicked();

    void on_level3Btn_clicked();

    void on_act1Btn_clicked();

    void on_act2Btn_clicked();

    void on_end4Btn_clicked();

    void on_prologueBtn_clicked();

    void on_end1Btn_clicked();

    void on_end2Btn_clicked();

    void on_end3Btn_clicked();

    void on_extraChapter_clicked();

private:
    Ui::MenuWindow *ui;
    SetDialog* setDlg;
    HelpDialog* helpDlg;
    QMediaPlayer* player;
    QAudioOutput* audio;
    Game& statistics;
};

#endif // MENUWINDOW_H
//修改effect音量同时要对setDailog
