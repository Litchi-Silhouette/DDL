#ifndef ACTWINDOW_H
#define ACTWINDOW_H

#include "../windowbase.h"
#include "../start_menu/set_help_acc.h"
#include "../Game.hpp"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class ActWindow; }
QT_END_NAMESPACE

class ActWindow : public windowBase
{
    Q_OBJECT

public:
    ActWindow(Game& game, int index, QWidget *parent = nullptr);
    //0:pro 1:act1 2:act2 3:end4 4:extra
    ~ActWindow();
protected:
    void showEvent(QShowEvent*);
private:
    Ui::ActWindow *ui;
    QString path;
    QVideoWidget* video;
    QMediaPlayer* player;
    QAudioOutput* audio;
    AccDialog* acc = nullptr;
    QPushButton* p;
    int pageindex;
    Game& statistics;
    QSoundEffect* buttom;
    CoverMask* curMask;
};
#endif // ACTWINDOW_H
