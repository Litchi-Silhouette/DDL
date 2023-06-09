#include "set_help_acc.h"

HelpDialog::HelpDialog(Game& game, QWidget* parent)
    :MyDialog(parent), subLay(nullptr), statistics(game)
{
    content = new QWidget(this);

    title = new QLabel("游戏规则", this);
    title->setFont(QFont("STKaiti", 32, QFont::Bold));
    title->setAlignment(Qt::AlignCenter);

    back = new QPushButton("",this);
    back->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/pic/image/go_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/pic/image/go_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/pic/image/go.png);}"
                  "QPushButton:focus{outline: none;}"
                  );
    back->setFixedSize(80,80);
    back->setFocus();
    back->setDefault(true);
    back->setFocusPolicy(Qt::StrongFocus);
    back->setShortcut(QKeySequence(Qt::Key_B));
    connect(back, &QPushButton::clicked, this, [=](){
        helpClose->play();
        helpClose->setMuted(!statistics.audioMode);
        helpClose->setVolume((double)statistics.effect/10);
        emit end();
        close();
    });

    helpClose = new QSoundEffect(this);
    helpClose->setSource(QUrl("qrc:/effects/sounds/help_close.wav"));

    center = new QScrollArea(this);
    //center->setBackgroundRole(QPalette::Dark);
    center->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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
    mainLay->addWidget(center,0, Qt::AlignCenter);
    mainLay->addWidget(back, 1, Qt::AlignCenter);

    setLayout(mainLay);
    setStyleSheet("QDialog{background: rgba(248, 248, 255, 150);}");
    setContent();
}

HelpDialog::~HelpDialog()
{
    delete center;
    delete back;
    delete title;
    delete helpClose;
}

void HelpDialog::resetFont(const QFont& cur){
    content->setFont(cur);
}

void HelpDialog::addContent(const QString& text){
    auto p = new QLabel(text, content);
    p->setFont(QFont("STKaiti", 16, QFont::Bold));
    p->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    subLay->insertWidget(subLay->count() - 1, p);
}

void HelpDialog::setContent(){
    if(content->layout()!=nullptr)
    {
        while (QLayoutItem* item = content->layout()->takeAt(0))
        {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
            delete item;
        }
        delete content->layout();
    }
    subLay = new QVBoxLayout;
    subLay->setContentsMargins(5,10,5,10);
    subLay->setSpacing(10);
    subLay->addStretch();
    content->setLayout(subLay);

    addContent("  欢迎各位来到P大！");
    addContent("  你将在这里扮演一名攻城狮，沉浸式体验P大大一信科的真实生活。\n  在日常的学习生活中，总有DDL怪兽拦住你的去路，现在到你大展身手的时间了！\n  在接下来的三个关卡中尽力击败它，博取光明的未来吧！");
    if(statistics.getLevels[1])
    {
        addContent("  第一关");
        addContent("  用键盘WASD键控制攻城狮的移动\n  地图上出现任务时，及时使攻城狮移动到任务所在位置\n  完成或失败的任务达上限即可通过关卡\n  任务被Deadline追上，扣除一定生命值\n  攻城狮被Deadline追上或生命值归零，本关失败");
    }
    if(statistics.getLevels[2])
    {
        addContent("  第二关");
        addContent("  按住鼠标左键并拖动，用鼠标拖拽的方式给予攻城狮一个初速度\n  地图上出现任务时，及时使攻城狮移动到任务所在位置\n  所有任务都出现后通过关卡\n  攻城狮被DDL怪兽追上一次或未完成任务，扣除一定生命值\n  生命值归零，本关失败");
    }
    if(statistics.getLevels[3])
    {
        addContent("  第三关");
        addContent("  用鼠标位置牵引的方式给予攻城狮一个加速度，使攻城狮向鼠标位置加速移动\n  地图上出现任务时，及时使攻城狮移动到任务所在位置\n  完成任务击败DDL即可通过关卡\n  DDL怪兽会向攻城狮发射子弹，攻城狮被子弹击中一次，扣除一定生命值\n  生命值归零，本关失败");
    }
    addContent("  快捷键");
    addContent("  开始界面：按E进入。\n  菜单界面：帮助：H，设置：S，退出：esc，返回：B，静音：M，重置：R\n                      关卡剧情部分由数字构成\n  剧情&结局：N下翻\n  关卡：P暂停，B返回主菜单，R重新开始，C继续游戏\n  提示：N关闭");
}

void HelpDialog::showEvent(QShowEvent* event){
    MyDialog::showEvent(event);
    setContent();
    back->setFocus(Qt::ActiveWindowFocusReason);
}

SetDialog::SetDialog(Game& game, QAudioOutput* _audio,QWidget* parent)
    :MyDialog(parent), audioInherit(_audio), statistics(game)
{
    auto tempTitle = QFont("华文楷体", 20, QFont::Bold);
    auto tempNum = QFont("华文楷体", 14, QFont::Bold);
    content = new QWidget(this);
    tip1 = new QLabel("音乐 ", content);
    tip2 = new QLabel("音效 ", content);
    tip3 = new QLabel("声音 ", content);
    tip4 = new QLabel("重置 ", content);
    tip1->setFont(tempTitle);
    tip2->setFont(tempTitle);
    tip3->setFont(tempTitle);
    tip4->setFont(tempTitle);
    num1 = new QLabel(" ", content);
    num1->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    num1->setFont(tempNum);
    num2 = new QLabel(" ", content);
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

    change1 = new QSlider(Qt::Horizontal, content);
    change2 = new QSlider(Qt::Horizontal, content);
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

    audio = new QPushButton("",content);
    audio->setFixedSize(80,80);
    connect(audio, &QPushButton::clicked, this, &SetDialog::changeMode);
    audio->setShortcut(QKeySequence(Qt::Key_M));

    back = new QPushButton("",content);
    back->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/pic/image/go_nor_gray.png);}"
                  "QPushButton:hover{border-image:url(:/pic/image/go_gray.png);}"
                  "QPushButton:pressed{border-image:url(:/pic/image/go.png);}"
                  "QPushButton:focus{outline: none;}"
                  );
    back->setFixedSize(80,80);
    back->setDefault(true);
    back->setFocusPolicy(Qt::StrongFocus);
    back->setShortcut(QKeySequence(Qt::Key_B));
    connect(back, &QPushButton::clicked, this, [=](){
        setClose->play();
        setClose->setMuted(!statistics.audioMode);
        setClose->setVolume((double)statistics.effect/10);
        close();
    });

    setClose = new QSoundEffect(this);
    setClose->setSource(QUrl("qrc:/effects/sounds/set_close.wav"));

    reset = new QPushButton("",content);
    reset->setStyleSheet("QPushButton{border:0px;"
                  "border-image:url(:/pic/image/restart_gray.png);}"
                  "QPushButton:hover{border-image:url(:/pic/image/restart.png);}"
                  "QPushButton:focus {outline: 1px solid black; outline-radius: 5px;}"
                  );
    reset->setFixedSize(80,80);
    reset->setShortcut(QKeySequence(Qt::Key_R));
    connect(reset, &QPushButton::clicked, this, &SetDialog::resetGame);

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

    content->setLayout(mainLay);
    content->adjustSize();
    content->setFixedSize(content->size());
    auto lay = new QVBoxLayout;
    lay->addWidget(content, 0, Qt::AlignCenter);
    setLayout(lay);
    setStyleSheet("QDialog{background: rgba(248, 248, 255, 150);}");
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
    delete setClose;
}

void SetDialog::setIni(){
    change1->setValue(statistics.music*10);
    change2->setValue(statistics.effect*10);
}

void SetDialog::setPattern(bool on)
{
    if(on)
        audio->setStyleSheet("QPushButton{border:0px;"
                      "border-image:url(:/pic/image/voice_on_gray.png);}"
                      "QPushButton:hover{border-image:url(:/pic/image/voice_on.png);}"
                      "QPushButton:focus {outline: 1px solid black; outline-radius: 5px;}"
                      );
    else
        audio->setStyleSheet("QPushButton{border:0px;"
                      "border-image:url(:/pic/image/voice_off_gray.png);}"
                      "QPushButton:hover{border-image:url(:/pic/image/voice_off.png);}"
                      "QPushButton:focus {outline: 1px solid black; outline-radius: 5px;}"
                      );
}

void SetDialog::resetGame(){
    for(int i=0;i<4;++i){
        statistics.getLevels[i] = 0;
        statistics.getActs[i] = 0;
        statistics.getEndings[i] = 0;
    }
    statistics.getEndings[4] = 0;
    statistics.getActs[0] = true;
    emit progressChanged();
}

void SetDialog::changeMode(){
    statistics.audioMode ^= 1;
    setPattern(statistics.audioMode);
    audioInherit->setMuted(!statistics.audioMode);
}

void SetDialog::changeAudio(int cur){
    num1->setText(QString("%1").arg(cur/10));
    statistics.music = cur/10;
    audioInherit->setVolume((double)statistics.music/10);
}
void SetDialog::changeEffect(int cur){
    num2->setText(QString("%1").arg(cur/10));
    statistics.effect = cur/10;
}

void SetDialog::showEvent(QShowEvent* event){
    MyDialog::showEvent(event);
    setIni();
    back->setFocus(Qt::ActiveWindowFocusReason);
    setPattern(statistics.audioMode);
}

AccDialog::AccDialog(Game& game,int index, QWidget* parent)
    :MyDialog(parent), statistics(game)
{
    btn = new QPushButton("",this);
    btn->setStyleSheet("QPushButton{border-image:url(:/pic/image/accomplish.png);"
                        "text-align: left; padding-left: 50px; color: black;"
                       "font : bold 14pt \"STKaiti\"; background: transparent;}"
                       "QPushButton:focus{outline: none;}"
                       );
    btn->setShortcut(QKeySequence(Qt::Key_B));
    btn->setDefault(true);
    btn->setFixedSize(350,80);
    btn->setVisible(false);
    connect(btn, &QPushButton::clicked, this, [=](){
        buttom->play();
        buttom->setMuted(!statistics.audioMode);
        buttom->setVolume((double)statistics.effect/10);
        emit end();
        close();
    });
    buttom = new QSoundEffect(this);
    buttom->setSource(QUrl("qrc:/effects/sounds/buttom3.wav"));
    start = new QSoundEffect(this);
    start->setSource(QUrl("qrc:/effects/sounds/accomplish.wav"));

    info = new QLabel("   ",this);
    info->setFont(QFont("STKaiti", 19, QFont::Bold));
    info->setAlignment(Qt::AlignCenter);
    info->adjustSize();
    info->setFixedHeight(info->height());
    pic = new QLabel(this);
    pic->setAlignment(Qt::AlignCenter);
    pic->setFixedSize(700,400);
    pic->setStyleSheet("background: rgba(248,248,255,1)");
    pic->setFrameShape(QFrame::Box);
    pic->setFrameShadow(QFrame::Sunken);
    pic->setLineWidth(3);
    pic->setMidLineWidth(3);

    auto mainLay = new QVBoxLayout;
    mainLay->setSpacing(20);
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->addStretch();
    mainLay->addWidget(pic, 0, Qt::AlignHCenter | Qt::AlignBottom);
    mainLay->addWidget(info, 0);
    mainLay->addWidget(btn, 0, Qt::AlignCenter);
    mainLay->addStretch();
    setLayout(mainLay);
    setStyleSheet("QDialog{background: rgba(248, 248, 255, 150);}");
    setIndex(index);
}

AccDialog::~AccDialog()
{
    delete btn;
    delete info;
    delete pic;
    delete buttom;
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
        acc = " 结局成就\n 习得性无助(´･_･`) ";
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
    start->play();
    start->setMuted(!statistics.audioMode);
    start->setVolume((double)statistics.effect/10);
    QTimer::singleShot(1000,this, [=](){
        buttom->play();
        buttom->setMuted(!statistics.audioMode);
        buttom->setVolume((double)statistics.effect/10);
        btn->show();
    });
    MyDialog::showEvent(event);
}
