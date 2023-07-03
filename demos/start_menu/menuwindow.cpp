#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(Game& game, QWidget *parent) :
    windowBase(parent),
    ui(new Ui::MenuWindow),
    setDlg(new SetDialog(game, this)),
    helpDlg(new HelpDialog(this)),
    statistics(game)
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
    helpDlg->exec();
}


void MenuWindow::on_setBtn_clicked()
{
    setDlg->exec();
    updateBtn();
}


void MenuWindow::on_exitBtn_clicked()
{
    emit changeWindow(-1);
    close();
}

void MenuWindow::updateBtn(){
    ui->level1Btn->setVisible(statistics.getLevels[1]);
    ui->level2Btn->setVisible(statistics.getLevels[2]);
    ui->level3Btn->setVisible(statistics.getLevels[3]);

    ui->act1Btn->setVisible(statistics.getActs[1]);
    ui->act1Label->setVisible(statistics.getActs[1]);
    ui->act2Btn->setVisible(statistics.getActs[2]);
    ui->act2Label->setVisible(statistics.getActs[2]);
    ui->prologueBtn->setVisible(statistics.getActs[0]);
    ui->proLabel->setVisible(statistics.getActs[0]);

    ui->end1Btn->setVisible(statistics.getEndings[1]);
    ui->end1Label->setVisible(statistics.getEndings[1]);
    ui->end2Btn->setVisible(statistics.getEndings[2]);
    ui->end2Label->setVisible(statistics.getEndings[2]);
    ui->end3Btn->setVisible(statistics.getEndings[3]);
    ui->end3Label->setVisible(statistics.getEndings[3]);
    ui->end4Btn->setVisible(statistics.getEndings[4]);
    ui->end4Label->setVisible(statistics.getEndings[4]);

    if(statistics.getEndings[1] && statistics.getEndings[3]
        && statistics.getEndings[2] && statistics.getEndings[4])
        statistics.getActs[3] = true;
    ui->extraChapter->setVisible(statistics.getActs[3]);
    ui->extraLabel->setVisible(statistics.getActs[3]);
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

