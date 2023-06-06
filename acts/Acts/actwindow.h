#ifndef ACTWINDOW_H
#define ACTWINDOW_H

#include "windowbase.h"
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class ActWindow; }
QT_END_NAMESPACE

class ActWindow : public windowBase
{
    Q_OBJECT

public:
    ActWindow(int index, QWidget *parent = nullptr);
    //0:pro 1:act1 2:act2 3:end4 4:extra
    ~ActWindow();
protected:
    void showEvent(QShowEvent*);
private:
    Ui::ActWindow *ui;
    QString path;
    QVideoWidget* video;
    QMediaPlayer* player;
    QPushButton* p;
    int pageindex;
};
#endif // ACTWINDOW_H
