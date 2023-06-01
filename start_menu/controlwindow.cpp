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
    QMainWindow(parent),
    ui(new Ui::ControlWindow),
    mainWidget(new QStackedWidget(this)),
    load(new LoadWindow),
    start(new StartWindow),
    menu(new MenuWindow(statics))
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    QIcon window(QString(":/pic/image/icon_w.png"));
    setWindowIcon(window);
    setWindowTitle(QString("Escape form Dead Line!"));

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
    menu->updateBtn();
}

ControlWindow::~ControlWindow()
{
    delete ui;
    delete mainWidget;
    delete load;
    delete start;
    delete menu;
    //if(on)
    //    delete on;
}

void ControlWindow::toWindow(int index)
{
    if(index!=-1)
        mainWidget->setCurrentIndex(index);
    else
        close();
}

void ControlWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);
    mainWidget->setCurrentIndex(0);
}

void ControlWindow::toLevel1()
{

}

void ControlWindow::toLevel2()
{

}

void ControlWindow::toLevel3()
{

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
                    statics.getLevels[i] = cur.toBool();
            }
        }else sig = false;

        if(obj.contains("act")){
            auto acts = obj.value("act").toArray();
            for(int i=0;i<acts.size();++i){
                auto cur = acts.at(i);
                if(cur.isBool())
                    statics.getActs[i] = cur.toBool();
            }
        }else sig = false;

        if(obj.contains("ending")){
            auto endings = obj.value("ending").toArray();
            for(int i=0;i<endings.size();++i){
                auto cur = endings.at(i);
                if(cur.isBool())
                    statics.getEndings[i] = cur.toBool();
            }
        }else sig = false;
    }
    return sig;
}

bool ControlWindow::dumpStatics()
{
    QJsonObject obj;
    QJsonArray levels;
    for(int i=0;i<4;++i){
        levels.append(statics.getLevels[i]);
    }
    obj.insert("level", levels);

    QJsonArray acts;
    for(int i=0;i<4;++i){
        acts.append(statics.getLevels[i]);
    }
    obj.insert("act", acts);

    QJsonArray endings;
    for(int i=0;i<5;++i){
        endings.append(statics.getLevels[i]);
    }
    obj.insert("ending", endings);

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
