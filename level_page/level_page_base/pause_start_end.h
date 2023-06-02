#include"Game.hpp"
#include<QLabel>
#include <QLayout>

#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H

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

#ifndef ENDDIALOG_H
#define ENDDIALOG_H

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
