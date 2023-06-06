#include "windowbase.h"
#include "ui_windowbase.h"

windowBase::windowBase(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::windowBase)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/page/level_image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));
}

windowBase::~windowBase()
{
    delete ui;
}
