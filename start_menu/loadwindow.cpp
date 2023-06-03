#include "loadwindow.h"
#include "ui_loadwindow.h"
#include <QTimerEvent>
#include <QLayout>
#include <QPainter>

LoadWindow::LoadWindow(QWidget *parent):
    windowBase(parent),
    ui(new Ui::LoadWindow)
{
    ui->setupUi(this);

    center = new StartDialog(this);
    center->setAttribute(Qt::WA_DeleteOnClose, true);
    center->resetFont(QFont("STKaiti", 20, QFont::Bold));
    center->setStartText("     3W    出品", 60);
    center->setMinimumSize(550,200);

    curMask = new CoverMask;
    connect(curMask, &CoverMask::closeEnd, this, &LoadWindow::close);
}

LoadWindow::~LoadWindow(){
    delete ui;
}

void LoadWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
    curMask->setGeometry(rect());
    curMask->show();
    QTimer::singleShot(100,center, &StartDialog::show);
    QTimer::singleShot(1000, curMask, &CoverMask::startShow);
    QTimer::singleShot(3000, curMask, &CoverMask::startClose);
}

void LoadWindow::hideEvent(QHideEvent* event){
    QMainWindow::hideEvent(event);
    center->close();
    emit changeWindow(1);
}
