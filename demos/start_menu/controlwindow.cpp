#include "controlwindow.h"
#include "ui_controlwindow.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

ControlWindow::ControlWindow(QWidget *parent) :
    windowBase(parent),
    ui(new Ui::ControlWindow),
    mainWidget(new QStackedWidget(this)),
    load(new LoadWindow),
    start(new StartWindow),
    menu(new MenuWindow(statistics))
{
    ui->setupUi(this);

    ui->verticalLayout->setContentsMargins(0,0,0,0);
    ui->verticalLayout->setSpacing(0);
    ui->verticalLayout->addWidget(mainWidget);
    mainWidget->addWidget(load);
    mainWidget->addWidget(start);
    mainWidget->addWidget(menu);

    connect(load, &LoadWindow::changeWindow, this, &ControlWindow::toWindow);
    connect(start, &StartWindow::changeWindow, this, &ControlWindow::toWindow);
    connect(menu, &MenuWindow::changeWindow, this, &ControlWindow::toWindow);

    loadStatics("X:\\GitHub_pro\\DDL\\start_menu\\statics.json");
}

ControlWindow::~ControlWindow()
{
    delete ui;
    delete mainWidget;
}

void ControlWindow::toWindow(int index)
{
    if(0<=index && index<10)
        mainWidget->setCurrentIndex(index);
    else if(index == -1){
        dumpStatics();
        close();
    }else
    {
        if(curWindow){
            mainWidget->removeWidget(curWindow);
            delete curWindow;
        }
        switch(index){
        case 10:
            //curWindow = new QMainWindow(this);
            break;
        case 21:
            //curWindow = new MainWindowOne;
            break;
        case 22:
            //curWindow = new MainWindowTwo;
            break;
        case 23:
            //curWindow = new MainWindowThree;
            break;
        default:
            qDebug()<<"unavailable index"<<index;
            exit(0);
            break;
        }
        mainWidget->addWidget(curWindow);
        connect(curWindow, &windowBase::changeWindow, this, &ControlWindow::toWindow);
        mainWidget->setCurrentWidget(curWindow);
    }
}

void ControlWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);
    mainWidget->setCurrentIndex(0);
}

bool ControlWindow::loadStatics(const QString& _path)
{
    bool sig = true;
    if(_path != "")
        path = _path;
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
        if(obj.contains("level")){
            auto levels = obj.value("level").toArray();
            for(int i=0;i<levels.size();++i){
                auto cur = levels.at(i);
                if(cur.isBool())
                    statistics.getLevels[i] = cur.toBool();
            }
        }else sig = false;

        if(obj.contains("act")){
            auto acts = obj.value("act").toArray();
            for(int i=0;i<acts.size();++i){
                auto cur = acts.at(i);
                if(cur.isBool())
                    statistics.getActs[i] = cur.toBool();
            }
        }else sig = false;

        if(obj.contains("ending")){
            auto endings = obj.value("ending").toArray();
            for(int i=0;i<endings.size();++i){
                auto cur = endings.at(i);
                if(cur.isBool())
                    statistics.getEndings[i] = cur.toBool();
            }
        }else sig = false;

        if(obj.contains("audio")){
            auto cur = obj.value("audio");
            if(cur.isBool())
                statistics.audioMode = cur.toBool();

        }else sig = false;

        if(obj.contains("effect")){
            auto cur = obj.value("effect");
            if(cur.isDouble())
                statistics.effect = cur.toDouble();

        }else sig = false;

        if(obj.contains("music")){
            auto cur = obj.value("music");
            if(cur.isDouble())
                statistics.music = cur.toDouble();

        }else sig = false;
    }
    return sig;
}

bool ControlWindow::dumpStatics()
{
    QJsonObject obj;
    QJsonArray levels;
    for(int i=0;i<4;++i){
        levels.append(statistics.getLevels[i]);
    }
    obj.insert("level", levels);

    QJsonArray acts;
    for(int i=0;i<4;++i){
        acts.append(statistics.getActs[i]);
    }
    obj.insert("act", acts);

    QJsonArray endings;
    for(int i=0;i<5;++i){
        endings.append(statistics.getEndings[i]);
    }
    obj.insert("ending", endings);
    obj.insert("audio", QJsonValue(statistics.audioMode));
    obj.insert("effect", QJsonValue(statistics.effect));
    obj.insert("music", QJsonValue(statistics.music));

    QJsonDocument doc;
    doc.setObject(obj);
    bool sig = true;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "can't open error!";
        sig = false;
    }
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    stream<<doc.toJson();
    file.close();

    return sig;
}
