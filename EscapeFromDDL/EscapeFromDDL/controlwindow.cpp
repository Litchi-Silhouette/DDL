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
    load(new LoadWindow),
    start(new StartWindow(statistics)),
    menu(new MenuWindow(statistics))
{
    ui->setupUi(this);

    mainWidget = new QStackedWidget(ui->centralwidget);
    mainWidget->addWidget(load);
    mainWidget->addWidget(start);
    mainWidget->addWidget(menu);

    connect(load, &LoadWindow::changeWindow, this, &ControlWindow::toWindow);
    connect(start, &StartWindow::changeWindow, this, &ControlWindow::toWindow);
    connect(menu, &MenuWindow::changeWindow, this, &ControlWindow::toWindow);
    connect(this, &ControlWindow::changeWindow, this, &ControlWindow::toWindow);

    loadStatics();
}

ControlWindow::~ControlWindow()
{
    delete ui;
    delete mainWidget;
}

void ControlWindow::resizeEvent(QResizeEvent* event){
    windowBase::resizeEvent(event);
    QSize tmpsize = event->size();
    QSize new_size = event->size();
    if(width_ratio && height_ratio)
    {
        if(new_size.width()<width_ratio*new_size.height()/height_ratio)
            new_size.setHeight(height_ratio*new_size.width()/width_ratio);
        if(new_size.width()>width_ratio*new_size.height()/height_ratio)
            new_size.setWidth(width_ratio*new_size.height()/height_ratio);
    }
    mainWidget->setGeometry((tmpsize.width() - new_size.width())/2,
                            (tmpsize.height() - new_size.height())/2,
                            new_size.width(),new_size.height());
}

void ControlWindow::toWindow(int index)
{
    if(0<=index && index<3)
        mainWidget->setCurrentIndex(index);
    else if(index == -1){
        dumpStatics();
        close();
    }else
    {
        switch(index){
        case 3:
            tmpWindow = new ActWindow(statistics,4,this);
            break;
        case 10:
            tmpWindow = new ActWindow(statistics,0);
            break;
        case 11:
            tmpWindow = new ActWindow(statistics,1);
            break;
        case 12:
            tmpWindow = new ActWindow(statistics,2);
            break;
        case 13:
            tmpWindow = new ActWindow(statistics,3);
            break;
        case 21:
            tmpWindow = new MainWindowOne(statistics);
            break;
        case 22:
            tmpWindow = new MainWindowTwo(statistics);
            break;
        case 23:
            tmpWindow = new MainWindowThree(statistics);
            break;
        case 31:
            tmpWindow = new EndingWindow(statistics, 1);
            break;
        case 32:
            tmpWindow = new EndingWindow(statistics, 2);
            break;
        case 33:
            tmpWindow = new EndingWindow(statistics, 3);
            break;
        default:
            qDebug()<<"unavailable index"<<index;
            exit(0);
            break;
        }
        if(tmpWindow)
        {
            mainWidget->addWidget(tmpWindow);
            connect(tmpWindow, &windowBase::changeWindow, this, &ControlWindow::toWindow);
            mainWidget->setCurrentWidget(tmpWindow);
        }
        QTimer::singleShot(500, this, [=](){
            if(curWindow){
                mainWidget->removeWidget(curWindow);
                delete curWindow;
                curWindow = nullptr;
            }
            curWindow = tmpWindow;
            tmpWindow = nullptr;
        });
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
    }else
    {
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
    }
    return sig;
}

void ControlWindow::dumpStatics()
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

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    stream<<doc.toJson();
    file.close();
}
