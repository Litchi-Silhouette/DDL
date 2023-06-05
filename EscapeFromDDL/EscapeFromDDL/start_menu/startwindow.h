#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "../windowbase.h"
#include "../Game.hpp"
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public windowBase
{
    Q_OBJECT

public:
    StartWindow(Game& game,QWidget *parent = nullptr);
    ~StartWindow();

protected:
    void paintEvent(QPaintEvent*);
    void hideEvent(QHideEvent* );
    void showEvent(QShowEvent* );
    void startBlink();
    void stayRed();
    void blink();
private:
    Ui::StartWindow *ui;
    QTimer* p;
    QString nor = ":/pic/image/page_w.png";
    QString on = ":/pic/image/page_r.png";
    int index = 0;
    int interval = 100;
    QMediaPlayer* player;
    QAudioOutput* audio;
    Game& statistics;
};
#endif // STARTWINDOW_H
