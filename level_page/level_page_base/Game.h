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

class Game{
public:
    QMainWindow* start;
    QMainWindow* menu;
    QMainWindow* end;

    QHash<int , QMainWindow*> intervals;
    QHash<int , QMainWindow*> ends;
    QHash<int , QMainWindow*> levels;

    QHash<int , ItemHash*> all_tasks;
    QHash<int , ItemHash*> all_buffs;
    QHash<int , QListWidgetItem*> all_items;

    QMainWindow* nextlevel(int temp){
        return levels[temp];
    }
};

#endif // GAME_H
