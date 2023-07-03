#include "tipdialog.h"
#include "ui_tipdialog.h"

TipDialog::TipDialog(int level, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TipDialog)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::FramelessWindowHint;
    flags |= Qt::Tool;                 //程序不在任务栏显示
    flags |= Qt::WindowStaysOnTopHint; //置顶显示
    setWindowFlags(flags);
    setAttribute(Qt::WA_DeleteOnClose);
    showAnimation = new QPropertyAnimation(this, "tmpHeight");
    showAnimation->setDuration(300);
    closeAnimation = new QPropertyAnimation(this, "tmpHeight");
    closeAnimation->setDuration(300);

    tipOp = new QGraphicsOpacityEffect(ui->tip);
    tipOp->setOpacity(0);
    ui->tip->setGraphicsEffect(tipOp);
    titleOp = new QGraphicsOpacityEffect(ui->title);
    titleOp->setOpacity(0);
    ui->title->setGraphicsEffect(titleOp);

    tipShow = new QPropertyAnimation(tipOp, "opacity", this);
    tipShow->setDuration(200);
    tipShow->setStartValue(0.0);
    tipShow->setEndValue(1.0);

    titleShow = new QPropertyAnimation(titleOp, "opacity", this);
    titleShow ->setDuration(200);
    titleShow ->setStartValue(0.0);
    titleShow ->setEndValue(1.0);

    connect(showAnimation, &QPropertyAnimation::finished, this, [=](){
        tipShow->start();
        titleShow->start();
    });
    connect(closeAnimation, &QPropertyAnimation::finished, this, [=](){ emit closeEnd(); close(); });
    getText(level);
}

TipDialog::~TipDialog()
{
    delete ui;
    delete showAnimation;
    delete closeAnimation;
}

void TipDialog::showEvent(QShowEvent* event){
    if(parentWidget()!=nullptr){
        setFixedWidth(parentWidget()->width());
        heightFinal = 225;
    }else{
        setFixedWidth(1200);
        heightFinal = 225;
    }
    showAnimation->setStartValue(5);
    showAnimation->setEndValue(heightFinal);
    closeAnimation->setEndValue(5);
    closeAnimation->setStartValue(heightFinal);

    QDialog::showEvent(event);
    showAnimation->start();
}

void TipDialog::closeGradually(){
    ui->tip->hide();
    ui->title->hide();
    closeAnimation->start();
}

void TipDialog::on_pushButton_clicked()
{
    closeGradually();
}

void TipDialog::getText(int level){
    switch (level) {
    case 1:
        ui->tip->setText("• 使用键盘WASD移动角色\n• 在DDL降临前尽力完成所有任务，未完成任务会掉血\n• 永远不要试图越过DDL！！！(否则嘿嘿嘿…)");
        break;
    case 2:
        ui->tip->setText("• “点击左键-拉动鼠标-松开鼠标”给角色初速度\n• 在躲避DDL的追杀同时及时完成任务，否则都会扣血\n• 保持血线活（狗）到最后吧");
        break;
    case 3:
        ui->tip->setText("• 角色会向鼠标位置加速，注意角色有惯性哦\n• 狂舞吧,在各种子弹的风暴中！\n• 跟DDL殊死一战吧！！！这是你唯一的机会");
        break;
    default:
        ui->tip->setText("你来到了没有帮助的荒原……");
        break;
    }
}
