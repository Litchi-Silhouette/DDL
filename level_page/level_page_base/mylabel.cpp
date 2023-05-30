#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent, const QString& text)
    :QLabel(text, parent)
{
    QFont temp("Microsoft Yi Baiti",18,QFont::Bold);
    setMargin(0);
    setAlignment(Qt::AlignCenter);
    setFont(temp);
}

void MyLabel::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    auto temp = font();
    temp.setPixelSize(height()*3/4);
    setFont(temp);
}
