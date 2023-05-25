#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void hideEvent(QHideEvent* );
    void startBlink();
    void stayRed();
    void blink();
private:
    Ui::StartWindow *ui;
    QTimer* p;
    QString nor = ":/pic/image/page_w.png";
    QString on = ":/pic/image/page_r.png";
    int index = 0;
    int interval = 100;
};
#endif // STARTWINDOW_H
