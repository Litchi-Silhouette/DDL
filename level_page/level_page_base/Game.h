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
