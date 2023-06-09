#include "loadwindow.h"
#include "ui_loadwindow.h"
#include <QTimerEvent>
#include <QLayout>
#include <QPainter>

LoadWindow::LoadWindow(QWidget *parent):
    windowBase(parent),
    ui(new Ui::LoadWindow), first(true)
{
    ui->setupUi(this);

    center = new StartDialog(this);
    center->resetFont(QFont("STKaiti", 20, QFont::Bold));
    center->setMinimumSize(550,200);

    curMask = new CoverMask;
    connect(curMask, &CoverMask::closeEnd, this, [=](){
        if(first){
            center->close();
            center->setStartText("免责声明\n\n本产品仅供展示交流使用\n不做任何商业用途\n所有借鉴都在最后列出",36);
            ui->tip->hide();
            first = false;
            QTimer::singleShot(100,center, &StartDialog::show);
            QTimer::singleShot(1000, curMask, &CoverMask::startShow);
            QTimer::singleShot(3000, curMask, &CoverMask::startClose);
        }
        else
            close();
    });
}

LoadWindow::~LoadWindow(){
    delete ui;
    delete center;
    delete curMask;
}

void LoadWindow::showEvent(QShowEvent* event){
    QMainWindow::showEvent(event);
    curMask->setGeometry(rect());
    curMask->show();
    center->setStartText("3W    出品", 60);
    QTimer::singleShot(100,center, &StartDialog::show);
    QTimer::singleShot(1000, curMask, &CoverMask::startShow);
    QTimer::singleShot(3000, curMask, &CoverMask::startClose);
}

void LoadWindow::hideEvent(QHideEvent* event){
    QMainWindow::hideEvent(event);
    center->close();
    emit changeWindow(1);
    curMask->close();
}
