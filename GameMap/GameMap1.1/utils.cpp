#include "figure.h"
#include "ui_figure.h"
#include "gamemap.h"
#include "ui_gamemap.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QEvent>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QTimer>
#include <QDateTime>

//画格子工具
class GridWidget : public QWidget
{
public:
    int cellSize;
    int xCount; int yCount;
    int xStart; int yStart;

    GridWidget(QWidget *parent = nullptr, int _cellSize=40, int _xCount=30, int _yCount=12, int _xStart=40, int _yStart=200) :
        QWidget(parent)
    {
        cellSize = _cellSize;
        xCount = _xCount; yCount = _yCount;
        xStart = _xStart; yStart = _yStart;
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event)

        // 创建绘图设备
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制格子
        for (int row = 0; row < xCount; ++row) {
            for (int column = 0; column < yCount; ++column) {
                int x = xStart + row * cellSize;
                int y = yStart + column * cellSize;
                painter.drawRect(x, y, cellSize, cellSize);
            }
        }
    }
};




