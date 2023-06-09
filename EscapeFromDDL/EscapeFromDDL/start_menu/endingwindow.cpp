#include "endingwindow.h"
#include "ui_endingwindow.h"
#include <QTimer>
#include <QMouseEvent>

EndingWindow::EndingWindow(Game& game, int index, QWidget *parent) :
    windowBase(parent),
    ui(new Ui::EndingWindow),
    accDlg(new AccDialog(game, index, this)),
    statistics(game)
{
    ui->setupUi(this);
    path = QString(":/literature/ending/ending%1.json").arg(index);
    if(!load()){
        qDebug()<<"literature not full";
        exit(0);
    }
    ui->stackedWidget->setCurrentIndex(0);
    buttom = new QSoundEffect(this);
    buttom->setSource(QUrl("qrc:/effects/sounds/buttom2.wav"));

    ui->blank1->setFocus();
    ui->blank1->setDefault(true);
    connect(ui->blank1, &QPushButton::clicked, this, &EndingWindow::change);
    connect(ui->blank2, &QPushButton::clicked, this, &EndingWindow::change);
    connect(ui->blankS1, &QPushButton::clicked, this, &EndingWindow::change);
    connect(ui->blankS2, &QPushButton::clicked, this, &EndingWindow::change);
    connect(accDlg, &AccDialog::end, this, [=](){
        curMask->show();
        QTimer::singleShot(300, curMask, &CoverMask::close);
        emit changeWindow(2);
    });
}

EndingWindow::~EndingWindow()
{
    delete ui;
    delete accDlg;
    delete buttom;
}

void EndingWindow::nextText()
{
    ++pos;
    if(ui->stackedWidget->currentIndex()){
        if(pos >= page2Len)
            return;
        auto& tmp = literatrue[1][pos];
        auto cur = new QPushButton(tmp,this);
        cur->adjustSize();
        cur->setFixedHeight(cur->height());
        connect(cur, &QPushButton::clicked, this, &EndingWindow::change);
        ui->main2->removeWidget(ui->blankS2);
        ui->main2->addWidget(cur, 0, Qt::AlignCenter);
        ui->main2->addWidget(ui->blankS2);
    }else{
        if(pos >= page1Len)
            return;
        auto& tmp = literatrue[0][pos];
        auto cur = new QPushButton(tmp,this);
        cur->adjustSize();
        cur->setFixedHeight(cur->height());
        connect(cur, &QPushButton::clicked, this, &EndingWindow::change);
        ui->main1->removeWidget(ui->blankS1);
        ui->main1->addWidget(cur, 0, Qt::AlignCenter);
        ui->main1->addWidget(ui->blankS1);
    }
    update();
    QTimer::singleShot(interval, this, &EndingWindow::nextText);
}

bool EndingWindow::load()
{
    bool sig = true;

    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "can't open error!";
        sig = false;
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    auto text = stream.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
                sig = false;
    }
    if(!sig)
        return sig;
    if(doc.isObject()){
        auto obj = doc.object();
        if(obj.contains("page1")){
            auto page = obj.value("page1").toArray();
            for(int i=0;i<page.size();++i){
                auto cur = page.at(i);
                if(cur.isString())
                    literatrue[0][i] = cur.toString();
            }
            page1Len = page.size();
        }else sig = false;

        if(obj.contains("page2")){
            auto page = obj.value("page2").toArray();
            for(int i=0;i<page.size();++i){
                auto cur = page.at(i);
                if(cur.isString())
                    literatrue[1][i] = cur.toString();
            }
            page2Len = page.size();
        }else sig = false;
    }
    return sig;
}

void EndingWindow::showEvent(QShowEvent* event){
    windowBase::showEvent(event);
    curMask = new CoverMask;
    curMask->setGeometry(geometry());
    curMask->move(mapToGlobal(QPoint(0, 0)));
    QTimer::singleShot(1000, this, &EndingWindow::nextText);
}

void EndingWindow::change(){
    buttom->play();
    buttom->setMuted(!statistics.audioMode);
    buttom->setVolume((double)statistics.effect/10);
    if(ui->stackedWidget->currentIndex())
        accDlg->open();
    else
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->blank2->setFocus();
        ui->blank2->setDefault(true);
        pos = 0;
        QTimer::singleShot(1000, this, &EndingWindow::nextText);
    }
}
