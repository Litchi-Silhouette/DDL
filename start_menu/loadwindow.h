#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <QTimer>
#include "Game.hpp"
#include "windowbase.h"

namespace Ui {
class LoadWindow;
}

class LoadWindow : public windowBase
{
    Q_OBJECT

public:
    explicit LoadWindow(QWidget *parent = nullptr);
    ~LoadWindow();
protected:
    void showEvent(QShowEvent*) override;
    void hideEvent(QHideEvent*) override;
private:
    Ui::LoadWindow *ui;
    int updateTimer;
    StartDialog* center;
    CoverMask* curMask;

};

#endif // LOADWINDOW_H
