#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow),
    setDlg(new SetDialog(this)),
    helpDlg(new HelpDialog(this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/pic/image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_helpBtn_clicked()
{
    setBlur(30);
    helpDlg->exec();
    setBlur(0);
}


void MenuWindow::on_setBtn_clicked()
{
    setBlur(30);
    setDlg->exec();
    setBlur(0);
}


void MenuWindow::on_exitBtn_clicked()
{
    close();
}

void MenuWindow::setBlur(int extent){
    blureffect->setBlurRadius(extent);
    setGraphicsEffect(blureffect);
}
