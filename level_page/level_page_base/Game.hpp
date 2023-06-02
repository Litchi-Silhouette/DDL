#pragma once
#ifndef GAME_H
#define GAME_H

#include<QHash>
#include<QMainWindow>
#include<QListWidget>

class task_info{
    QPixmap icon;
    QString info;
    QString name;
    bool isRed;
public:
    explicit task_info(const QPixmap& _icon = QPixmap(), const QString& _name = "", const QString& _info = "", const bool& _isRed = false)
        :icon(_icon), info(_info), name(_name), isRed(_isRed){}
    QPixmap& geticon(){
        return icon;
    }
    QString& getname(){
        return name;
    }
    QString& getinfo(){
        return info;
    }
    bool& getRed(){
        return isRed;
    }
};

using ItemHash = QHash<QListWidgetItem*, task_info>;

struct Game{
    QHash<int , ItemHash*> all_tasks;
    QHash<int , ItemHash*> all_buffs;
    QHash<int , QListWidgetItem*> all_items;

    bool getEndings[5] = {};
    bool getLevels[4] = {};
    bool getActs[4] = {true};
};

#endif // GAME_H

#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

class MyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialog(QWidget *parent = nullptr)
        : QDialog{parent}
    {
        setMouseTracking(true);
        Qt::WindowFlags flags = Qt::Dialog;
        flags |= Qt::FramelessWindowHint;
        flags |= Qt::Tool;                 //程序不在任务栏显示
        flags |= Qt::WindowStaysOnTopHint; //置顶显示
        setWindowFlags(flags);
        setAttribute(Qt::WA_TranslucentBackground, true);
    }

signals:

};

#endif // MYDIALOG_H

#ifndef STARTDIALOG_H
#define STARTDIALOG_H
#include <QLabel>
#include <QLayout>

class StartDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit StartDialog(QWidget *parent = nullptr)
        :MyDialog(parent)
    {
        literature = new QLabel(this);
        literature->setFont(QFont("STHupo", 20, QFont::Bold));
        literature->setMinimumSize(400,200);
    }
    ~StartDialog(){
        delete literature;
    }
    void setStartText(const QString& _text, int fontSize){
        auto temp = literature->font();
        temp.setPointSize(fontSize);
        literature->setFont(temp);
        literature->setAlignment(Qt::AlignCenter);
        literature->setText(_text);
    }
    void resetFont(const QFont& cur){
        literature->setFont(cur);
    }
signals:
private:
    QLabel* literature;
};

#endif // STARTDIALOG_H
