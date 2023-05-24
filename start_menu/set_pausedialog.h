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
#include<QLabel>
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
