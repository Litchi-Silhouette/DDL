#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <QMainWindow>

namespace Ui {
class windowBase;
}

class windowBase : public QMainWindow
{
    Q_OBJECT

public:
    explicit windowBase(QWidget *parent = nullptr);
    ~windowBase();
signals:
    void changeWindow(int index);
private:
    Ui::windowBase *ui;
};

#endif // WINDOWBASE_H
