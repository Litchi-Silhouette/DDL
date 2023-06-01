#include "set_help_acc_start.h"

StartDialog::StartDialog(QWidget* parent)
    :MyDialog(parent)
{
    literature = new QLabel(this);
    literature->setFont(QFont("STHupo", 20, QFont::Bold));
    literature->setMinimumSize(400,200);
}

StartDialog::~StartDialog(){
    delete literature;
}

void StartDialog::resetFont(const QFont& cur){
    literature->setFont(cur);
}

void StartDialog::setStartText(const QString& _text, int fontSize){
    auto temp = literature->font();
    temp.setPointSize(fontSize);
    literature->setFont(temp);
    literature->setAlignment(Qt::AlignCenter);
    literature->setText(_text);
}

HelpDialog::HelpDialog(QWidget* parent)
    :MyDialog(parent)
{
    content = new QWidget(this);
    subLay = new QVBoxLayout;
    subLay->setContentsMargins(3,3,3,3);
    subLay->addStretch();
    content->setLayout(subLay);

    title = new QLabel("游戏规则", this);
    title->setFont(QFont("STKaiti", 32, QFont::Bold));
    title->setAlignment(Qt::AlignCenter);

    back = new QPushButton("",this);
    back->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/pic/image/go_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/pic/image/go_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/pic/image/go.png);}"
                  );
    back->setFixedSize(80,80);
    connect(back, &QPushButton::clicked, this, &HelpDialog::close);

    center = new QScrollArea(this);
    center->setBackgroundRole(QPalette::Dark);
    center->setFixedSize(800,450);
    center->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    center->setFrameStyle(QFrame::Box);
    center->setFrameShadow(QFrame::Sunken);
    center->setLineWidth(2);
    center->setMidLineWidth(2);
    center->setWidget(content);
    center->setWidgetResizable(true);

    auto mainLay = new QVBoxLayout(this);
    mainLay->setSpacing(10);
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->addWidget(title, 1, Qt::AlignCenter);
    mainLay->addWidget(center);
    mainLay->addWidget(back, 1, Qt::AlignCenter);

    setLayout(mainLay);
}

HelpDialog::~HelpDialog()
{
    delete center;
    delete content;
    delete back;
    delete title;
}

void HelpDialog::resetFont(const QFont& cur){
    content->setFont(cur);
}

void HelpDialog::setContent(const QString& text){
    auto p = new QLabel(text, content);
    p->setFont(QFont("STKaiti", 16, QFont::Bold));
    p->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    subLay->insertWidget(subLay->count() - 1, p);
}

SetDialog::SetDialog(QWidget* parent)
    :MyDialog(parent)
{
    auto tempTitle = QFont("华文楷体", 20, QFont::Bold);
    auto tempNum = QFont("华文楷体", 14, QFont::Bold);

    tip1 = new QLabel("音乐 ", this);
    tip2 = new QLabel("音效 ", this);
    tip3 = new QLabel("声音 ", this);
    tip4 = new QLabel("重置 ", this);
    tip1->setFont(tempTitle);
    tip2->setFont(tempTitle);
    tip3->setFont(tempTitle);
    tip4->setFont(tempTitle);
    num1 = new QLabel(" ", this);
    num1->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    num1->setFont(tempNum);
    num2 = new QLabel(" ", this);
    num2->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    num2->setFont(tempNum);

    QString cur = "QSlider::groove:horizontal {height: 6px;border-radius: 3px;left: 10px; right: 10px;}"
            //"background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(180, 180, 180, 255), stop:1 rgba(60, 60, 60, 255));}"
            "QSlider::sub-page:horizontal {background: rgb(70,70,70);border-radius: 3px;height: 6px;}"
            "QSlider::add-page:horizontal {background: rgb(220,220, 220);border-radius: 3px;height: 6px;}"
            "QSlider::handle:horizontal {background: rgb(193,204,208);width: 14px; "
                                        "border-radius: 7px; margin: -4px;}"
            "QSlider::handle:horizontal:hover {background: rgb(119,136,153); width: 18px; "
                                        "border-radius: 9px; margin: -6px;}";

    change1 = new QSlider(Qt::Horizontal, this);
    change2 = new QSlider(Qt::Horizontal, this);
    change1->setMaximum(100);
    change1->setMinimum(0);
    change1->setSingleStep(10);
    change1->setStyleSheet(cur);
    change2->setMaximum(100);
    change2->setMinimum(0);
    change2->setSingleStep(10);
    change2->setStyleSheet(cur);
    change1->setMinimumHeight(30);
    change2->setMinimumHeight(30);
    connect(change1, &QSlider::valueChanged, this, &SetDialog::changeAudio);
    connect(change2, &QSlider::valueChanged, this, &SetDialog::changeEffect);
    change1->setValue(5);
    change2->setValue(5);

    audio = new QPushButton("",this);
    audio->setFixedSize(80,80);
    connect(audio, &QPushButton::clicked, this, &SetDialog::changeMode);
    setPattern(true);

    back = new QPushButton("",this);
    back->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/pic/image/go_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/pic/image/go_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/pic/image/go.png);}"
                  );
    back->setFixedSize(80,80);
    connect(back, &QPushButton::clicked, this, &SetDialog::close);

    reset = new QPushButton("",this);
    reset->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/pic/image/restart_gray.png);}"
                  "QPushButton:hover{border-image:url(:/pic/image/restart.png);}"
                  );
    reset->setFixedSize(80,80);
    //connect(back, &QPushButton::clicked, this, &SetDialog::close);

    auto mainLay = new QGridLayout;
    mainLay->addWidget(tip1,0,0,1,1);
    mainLay->addWidget(tip2,1,0,1,1);
    mainLay->addWidget(tip3,2,0,1,1);
    mainLay->addWidget(tip4,2,2,1,1);
    mainLay->addWidget(change1,0,1,1,3);
    mainLay->addWidget(change2,1,1,1,3);
    mainLay->addWidget(num1,0,4,1,1);
    mainLay->addWidget(num2,1,4,1,1);
    mainLay->addWidget(reset,2,3,1,1);
    mainLay->addWidget(audio,2,1,1,1);
    mainLay->addWidget(back,3,1,1,2,Qt::AlignCenter);

    setLayout(mainLay);
}

SetDialog::~SetDialog()
{
    delete tip1;
    delete tip2;
    delete tip3;
    delete tip4;
    delete num1;
    delete num2;
    delete change1;
    delete change2;
    delete audio;
    delete reset;
    delete back;
}

void SetDialog::setPattern(bool on)
{
    if(on)
        audio->setStyleSheet("QPushButton{border:0px;"
                      "border-image:url(:/pic/image/voice_on_gray.png);}"
                      "QPushButton:hover{border-image:url(:/pic/image/voice_on.png);}"
                      );
    else
        audio->setStyleSheet("QPushButton{border:0px;"
                      "border-image:url(:/pic/image/voice_off_gray.png);}"
                      "QPushButton:hover{border-image:url(:/pic/image/voice_off.png);}"
                      );
}

void SetDialog::changeMode(){

}

void SetDialog::changeAudio(int cur){
    num1->setText(QString("%1").arg(cur/10));
}
void SetDialog::changeEffect(int cur){
    num2->setText(QString("%1").arg(cur/10));
}

AccDialog::AccDialog(QWidget* parent)
    :MyDialog(parent)
{
    btn = new QPushButton("",this);
    btn->setStyleSheet("QPushButton{border-image:url(:/pic/image/accomplish.png);"
                        "text-align: left; padding-left: 50px;}");
    btn->setFont(QFont("STKaiti", 14, QFont::Bold));
    btn->setFixedSize(350,80);
    btn->setVisible(false);
    connect(btn, &QPushButton::clicked, this, &AccDialog::close);
    info = new QLabel("",this);
    info->setFont(QFont("STKaiti", 18, QFont::Bold));
    info->setAlignment(Qt::AlignCenter);
    pic = new QLabel(this);
    pic->setAlignment(Qt::AlignCenter);
    pic->setFixedSize(700,400);
    pic->setStyleSheet("background: rgba(248,248,255,1)");
    pic->setFrameShape(QFrame::Box);
    pic->setFrameShadow(QFrame::Sunken);
    pic->setLineWidth(3);
    pic->setMidLineWidth(3);

    auto mainLay = new QVBoxLayout;
    mainLay->setSpacing(5);
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->addWidget(pic, 6);
    mainLay->addWidget(info, 1);
    mainLay->addWidget(btn, 1, Qt::AlignCenter);
    setLayout(mainLay);
}

AccDialog::~AccDialog()
{
    delete btn;
    delete info;
    delete pic;
}

void AccDialog::setIndex(int index)
{
    switch(index){
    case 1:
        picPath = ":/pic/image/ending1.png";
        iconPath = ":/pic/image/ending1icon.png";
        acc = " 结局成就\n 中道崩殂… ";
        info->setText("「 先狮创业未半而中道崩殂 」");
        break;
    case 2:
        picPath = ":/pic/image/ending2.png";
        iconPath = ":/pic/image/ending2icon.png";
        acc = " 结局成就\n 习得性无助(っ◞‸◟c) ";
        info->setText("「 可怜绩点无狮顾，惟余三和跳大神 」");
        break;
    case 3:
        picPath = ":/pic/image/ending3.png";
        iconPath = ":/pic/image/ending3icon.png";
        acc = " 结局成就\n 就凭你 也配直视我 ";
        info->setText("「 惊涛骇浪从容渡，越是艰难越向前 」");
        break;
    case 4:
        picPath = ":/pic/image/ending4.png";
        iconPath = ":/pic/image/ending4icon.png";
        acc = " 结局成就\n 真的猛士！ ";
        info->setText("「 真的猛士，敢于直面惨淡的狮生，敢于正视眼前的DDL 」");
        break;
    default:
        qDebug()<<"no ending";
        exit(0);
        break;
    }
    btn->setIconSize(QSize(60,60));
    btn->setIcon(QIcon(iconPath));
    btn->setText(acc);
    pic->setPixmap(QPixmap(picPath).scaled(pic->size(),Qt::KeepAspectRatio));
}

void AccDialog::showEvent(QShowEvent* event)
{
    QTimer::singleShot(1000,btn, &QPushButton::show);
    MyDialog::showEvent(event);
}
