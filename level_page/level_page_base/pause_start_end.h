#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H
#include"Game.hpp"
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
#include<QLabel>
#include <QLayout>
#include"Game.hpp"

class StartDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit StartDialog(QWidget *parent = nullptr);
    ~StartDialog();
    void setStartText(const QString& _text, int fontsize);
signals:
private:
    QLabel* literature;
};

#endif // STARTDIALOG_H

#ifndef ENDDIALOG_H
#define ENDDIALOG_H
#include<QLabel>
#include <QLayout>
#include"Game.hpp"

class EndDialog : public MyDialog
{
    Q_OBJECT
public:
    explicit EndDialog(QWidget *parent = nullptr);
    ~EndDialog();
    int getChoice(){
        return choice;
    }
signals:
private slots:
    void back();
    void next();
private:

    QLabel* literature;
    QPushButton* nextBtn;
    QPushButton* backBtn;
    int choice = 0;
};

#endif // ENDDIALOG_H

#ifndef MOVIEDIALOG_H
#define MOVIEDIALOG_H
#include<QLabel>
#include <QLayout>
#include"Game.hpp"

class MovieDialog : public MyDialog
{
    Q_OBJECT
public:
    //explicit MovieDialog(QWidget *parent = nullptr);
    //~MovieDialog();

signals:
private:
private slots:

};

#endif // MOVIEDIALOG_H
