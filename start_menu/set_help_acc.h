#include "Game.hpp"
#include <QPushButton>
#include <QLabel>

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QLayout>
#include <QScrollArea>

class HelpDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();
    void resetFont(const QFont&);
    void setContent(const QString&);
signals:
private:
    QWidget* content;
    QLabel* title;
    QPushButton* back;
    QScrollArea* center;
    QVBoxLayout* subLay;
};

#endif // HELPDIALOG_H

#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSlider>

class SetDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit SetDialog(QWidget *parent = nullptr);
    ~SetDialog();

signals:
private slots:
    void changeMode();
    void changeAudio(int);
    void changeEffect(int);
private:
    void setPattern(bool on);

    QLabel* tip1;
    QLabel* tip2;
    QLabel* tip3;
    QLabel* tip4;
    QLabel* num1;
    QLabel* num2;
    QSlider* change1;
    QSlider* change2;
    QPushButton* audio;
    QPushButton* reset;
    QPushButton* back;
};

#endif // SETDIALOG_H

#ifndef ACCDIALOG_H
#define ACCDIALOG_H

#include <QTimer>

class AccDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit AccDialog(QWidget *parent = nullptr);
    ~AccDialog();
    void setIndex(int);     //1-4:for accomplish index
protected:
    void showEvent(QShowEvent*);
signals:
private:
    QLabel* pic;
    QLabel* info;
    QPushButton* btn;
    QString picPath;
    QString iconPath;
    QString acc;
};

#endif // ACCDIALOG_H
