#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QLabel>

class MyLabel: public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget* parent = nullptr, const QString& text = "");
protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // MYQLABEL_H
