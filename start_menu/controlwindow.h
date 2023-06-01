#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "startwindow.h"
#include "loadwindow.h"
#include "menuwindow.h"
#include "Game.hpp"

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
    void toLevel1();
    void toLevel2();
    void toLevel3();
private:
    Ui::ControlWindow *ui;
    QStackedWidget* mainWidget;
    LoadWindow* load;
    StartWindow* start;
    MenuWindow* menu;
    QMainWindow* on = nullptr;
    Game statics;
    QString path;
};

#endif // CONTROLWINDOW_H
