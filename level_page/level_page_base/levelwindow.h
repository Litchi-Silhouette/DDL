#ifndef LEVELWINDOW_H
#define LEVELWINDOW_H

#include <QMainWindow>
#include "pause_button.h"
#include "live_bar.h"
#include "warning_icon.h"
#include "ddl_list.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class LevelWindow; }
QT_END_NAMESPACE

class LevelWindow : public QMainWindow
{
    Q_OBJECT

public:
    LevelWindow(QWidget *parent = nullptr,const int cur_level = 0);
    ~LevelWindow();

private slots:
    void pause();

private:
    Ui::LevelWindow *ui;
    pause_block* pause_b;
    live_bar* bar;
    warning_icon* warning;
    DDL_List* list;
    QFrame* map_border;
    QTimer* timer_update;

    int level;
    int live;
    int interval = 30;
};
#endif // LEVELWINDOW_H
