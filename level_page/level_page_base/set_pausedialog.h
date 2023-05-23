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

#include <QDialog>
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
    QPixmap mask = QPixmap(":/page/level_image/back_on_gray.png").scaled(80,80);
    int choice = 0;
};

#endif // MYDIALOG_H
