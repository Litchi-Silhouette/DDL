#include "windowbase.h"
#include "ui_windowbase.h"

windowBase::windowBase(QWidget *parent, bool isWhite) :
    QMainWindow(parent),
    ui(new Ui::windowBase)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/pic/image/icon_w.png"));
    setWindowIcon(window);
    if(isWhite)
        setStyleSheet("QMainWindow{background: rgb(248, 248, 255);}");
    else
        setStyleSheet("QMainWindow{background: rgb(23, 23, 23);}");
}

windowBase::~windowBase()
{
    delete ui;
}
