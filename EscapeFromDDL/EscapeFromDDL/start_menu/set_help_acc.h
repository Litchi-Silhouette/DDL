#include "../Game.hpp"
#include <QPushButton>
#include <QLabel>
#include <QSoundEffect>

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QLayout>
#include <QScrollArea>

class HelpDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit HelpDialog(Game& game, QWidget *parent = nullptr);
    ~HelpDialog();
    void resetFont(const QFont&);
    void addContent(const QString&);
signals:
    void end();
private:
    QWidget* content;
    QLabel* title;
    QPushButton* back;
    QScrollArea* center;
    QVBoxLayout* subLay;
    QSoundEffect* helpClose;
    Game& statistics;
};

#endif // HELPDIALOG_H

#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSlider>
#include "../Game.hpp"
#include <QAudioOutput>

class SetDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit SetDialog(Game& game, QAudioOutput* _audio, QWidget *parent = nullptr);
    ~SetDialog();
signals:
    void progressChanged();
private slots:
    void changeMode();
    void changeAudio(int);
    void changeEffect(int);
    void resetGame();
    void setIni();
protected:
    void showEvent(QShowEvent*);
private:
    void setPattern(bool on);
    QWidget* content;
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
    QAudioOutput* audioInherit;
    QSoundEffect* setClose;
    Game& statistics;
};

#endif // SETDIALOG_H

#ifndef ACCDIALOG_H
#define ACCDIALOG_H

#include <QTimer>

class AccDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit AccDialog(Game& game, int index, QWidget *parent = nullptr);
    ~AccDialog();
    void setIndex(int);     //1-4:for accomplish index
protected:
    void showEvent(QShowEvent*);
signals:
    void end();
private:
    QLabel* pic;
    QLabel* info;
    QPushButton* btn;
    QString picPath;
    QString iconPath;
    QString acc;
    QSoundEffect* buttom;
    Game& statistics;
};

#endif // ACCDIALOG_H
