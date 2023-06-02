#include "contolwindow.h"
#include "ui_contolwindow.h"

ContolWindow::ContolWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ContolWindow)
{
    ui->setupUi(this);
}

ContolWindow::~ContolWindow()
{
    delete ui;
}

