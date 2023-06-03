#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QStackedWidget>
#include "./start_menu/startwindow.h"
#include "./start_menu/loadwindow.h"
#include "./start_menu/menuwindow.h"
#include "./start_menu/endingwindow.h"
#include "./GameMap/init.cpp"
#include "./GameMap/obstacle.cpp"
#include "windowbase.h"
#include "Game.hpp"


namespace Ui {
class ControlWindow;
}

class ControlWindow : public windowBase
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();
    bool loadStatics(const QString& _path = "");
    void dumpStatics();
signals:
    void gameProgress(int);
protected slots:
    void showEvent(QShowEvent*);
private slots:
    void toWindow(int index);
    //0:load 1:start 2:menu 3:extra
    //10:prologue 11:act1 12:act2 13:ending4
    //21:level1 22:level2 23:level3
    //31:ending1 32:ending2 33:ending3
private:
    Ui::ControlWindow *ui;
    QStackedWidget* mainWidget;
    LoadWindow* load;
    StartWindow* start;
    MenuWindow* menu;
    windowBase* curWindow = nullptr;
    windowBase* tmpWindow = nullptr;
    Game statistics;
    QString path = ".//statistics.json";
};

#endif // CONTROLWINDOW_H
