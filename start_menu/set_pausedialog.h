#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

class MyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialog(QWidget *parent = nullptr);

signals:

};

#endif // MYDIALOG_H

#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H

#include <QLayout>
#include <QPushButton>

class PauseDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit PauseDialog(QWidget *parent = nullptr);
    ~PauseDialog();
    int getChoice() const;
signals:
private slots:
    void back();
    void restart();
    void conti();
private:
    QHBoxLayout* main_lay;
    QPushButton* backBtn;
    QPushButton* restartBtn;
    QPushButton* continueBtn;
    int choice = 0;
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
    explicit StartDialog(QWidget *parent = nullptr);
    ~StartDialog();
    void setStartText(const QString& _text, int fontsize);
    void resetFont(const QFont&);
signals:
private:
    QLabel* literature;
};

#endif // STARTDIALOG_H

#ifndef HELPDIALOG_H
#define HELPDIALOG_H
#include <QLabel>
#include <QLayout>
#include <QPushButton>
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

#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

class EndDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit EndDialog(QWidget *parent = nullptr);
    ~EndDialog();
    void setIndex(int);     //1-4:for accomplish index
signals:
private:
    QLabel* pic;
    QLabel* info;
    QTimer* t;
    QPushButton* btn;
};

#endif // ENDDIALOG_H
