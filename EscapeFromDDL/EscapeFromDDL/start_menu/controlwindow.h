#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "startwindow.h"
#include "loadwindow.h"
#include "menuwindow.h"
#include "../Game.hpp"
#include "GameMap3.3/init.cpp"
#include "GameMap3.3/obstacle.cpp"


namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();
    bool loadStatics(const QString& _path = "");
    bool dumpStatics();
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
    LevelWindow* curWindow = nullptr;
    Game statics;
    QString path;
};

#endif // CONTROLWINDOW_H
