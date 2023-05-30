#include "controlwindow.h"
#include "ui_controlwindow.h"

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow),
    mainWidget(new QStackedWidget(this)),
    load(new LoadWindow),
    start(new StartWindow),
    menu(new MenuWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/pic/image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));

    ui->verticalLayout->setContentsMargins(0,0,0,0);
    ui->verticalLayout->setSpacing(0);
    ui->verticalLayout->addWidget(mainWidget);
    mainWidget->addWidget(load);
    mainWidget->addWidget(start);
    mainWidget->addWidget(menu);

    connect(load, &LoadWindow::changeWindow, this, &ControlWindow::toWindow);
    connect(start, &StartWindow::changeWindow, this, &ControlWindow::toWindow);
    connect(menu, &MenuWindow::changeWindow, this, &ControlWindow::toWindow);
}

ControlWindow::~ControlWindow()
{
    delete ui;
    delete mainWidget;
}

void ControlWindow::toWindow(int index)
{
    if(index!=-1)
        mainWidget->setCurrentIndex(index);
    else
        close();
}

void ControlWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);
    mainWidget->setCurrentIndex(0);
}
