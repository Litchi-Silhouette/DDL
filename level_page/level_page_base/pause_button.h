#ifndef PAUSE_BUTTON_H
#define PAUSE_BUTTON_H

#include <QPushButton>

class pause_button : public QPushButton
{
    Q_OBJECT
public:
    explicit pause_button(const QString& text, QWidget *parent = nullptr);
    int heightForWidth(int w) const;
};

#endif // PAUSE_BUTTON_H

#ifndef PAUSE_BLOCK_H
#define PAUSE_BLOCK_H

#include "mylabel.h"
#include <QTimer>
#include <QResizeEvent>
class pause_block: public QWidget
{
    Q_OBJECT
public:
    explicit pause_block(const int cur_level,QWidget* parent = nullptr);
    ~pause_block();
    void start_time();
    void pause_time();
    pause_button* btn;

private slots:
    void update_time();
private:
    int level;
    MyLabel* time_l;
    MyLabel* time_t;
    MyLabel* level_l;
    MyLabel* level_t;
    QTimer* timer;
    int time;
};

#endif // PAUSE_BLOCK_H
