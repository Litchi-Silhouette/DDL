#ifndef ENDINGWINDOW_H
#define ENDINGWINDOW_H

#include "../windowbase.h"
#include "set_help_acc.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QSoundEffect>

namespace Ui {
class EndingWindow;
}

class EndingWindow : public windowBase
{
    Q_OBJECT

public:
    explicit EndingWindow(Game& game, int index, QWidget *parent = nullptr);
    ~EndingWindow();
    void nextText();
protected:
    void showEvent(QShowEvent*);

private slots:
    void change();
private:
    bool load();
    Ui::EndingWindow *ui;
    int pos = 0;
    AccDialog* accDlg;
    QString path;
    QString literatrue[2][10] = {};
    int page1Len = 0;
    int page2Len = 0;
    int interval = 2000;
    Game& statistics;
    QSoundEffect* buttom;
};

#endif // ENDINGWINDOW_H
