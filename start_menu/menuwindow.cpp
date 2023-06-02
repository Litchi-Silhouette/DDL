#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(Game& game, QWidget *parent) :
    windowBase(parent),
    ui(new Ui::MenuWindow),
    setDlg(new SetDialog(this)),
    helpDlg(new HelpDialog(this)),
    statics(game)
{
    ui->setupUi(this);
    ui->toolframe->layout()->setContentsMargins(10,0,10,0);
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
    emit changeWindow(-1);
    close();
}

void MenuWindow::setBlur(int extent){
    blureffect->setBlurRadius(extent);
    setGraphicsEffect(blureffect);
}

void MenuWindow::updateBtn(){
    ui->level1Btn->setVisible(statics.getLevels[1]);
    ui->level2Btn->setVisible(statics.getLevels[2]);
    ui->level3Btn->setVisible(statics.getLevels[3]);

    ui->act1Btn->setVisible(statics.getActs[1]);
    ui->act1Label->setVisible(statics.getActs[1]);
    ui->act2Btn->setVisible(statics.getActs[2]);
    ui->act2Label->setVisible(statics.getActs[2]);
    ui->prologueBtn->setVisible(statics.getActs[0]);
    ui->proLabel->setVisible(statics.getActs[0]);
    ui->extraChapter->setVisible(statics.getActs[3]);
    ui->extraLabel->setVisible(statics.getActs[3]);

    ui->end1Btn->setVisible(statics.getEndings[1]);
    ui->end1Label->setVisible(statics.getEndings[1]);
    ui->end2Btn->setVisible(statics.getEndings[2]);
    ui->end2Label->setVisible(statics.getEndings[2]);
    ui->end3Btn->setVisible(statics.getEndings[3]);
    ui->end3Label->setVisible(statics.getEndings[3]);
    ui->end4Btn->setVisible(statics.getEndings[4]);
    ui->end4Label->setVisible(statics.getEndings[4]);
}

void MenuWindow::on_level1Btn_clicked()
{
    emit changeWindow(21);
}

void MenuWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);
    updateBtn();
}

void MenuWindow::on_level2Btn_clicked()
{
    emit changeWindow(22);
}


void MenuWindow::on_level3Btn_clicked()
{
    emit changeWindow(23);
}

