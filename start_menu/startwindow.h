#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
protected:
    void paintEvent(QPaintEvent*);
private:
    Ui::StartWindow *ui;
    QString nor = "";
    QString on = "";
};
#endif // STARTWINDOW_H
