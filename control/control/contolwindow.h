#ifndef CONTOLWINDOW_H
#define CONTOLWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ContolWindow; }
QT_END_NAMESPACE

class ContolWindow : public QMainWindow
{
    Q_OBJECT

public:
    ContolWindow(QWidget *parent = nullptr);
    ~ContolWindow();

private:
    Ui::ContolWindow *ui;
};
#endif // CONTOLWINDOW_H
