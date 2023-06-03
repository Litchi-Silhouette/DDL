#include "init.cpp"

//工具函数

/*



//画格子工具
class GridWidget : public QWidget
{
public:
    int cellSize;
    int xCount; int yCount;
    int xStart; int yStart;

    GridWidget(QWidget *parent = nullptr, int _cellSize=MainWindow::CELL_SIZE, int _xCount=X_GRID_NUM-2, int _yCount=Y_GRID_NUM-2,
               int _xStart=MainWindow::CELL_SIZE, int _yStart=MainWindow::CELL_SIZE+MainWindow::Y_TOOL_HEIGHT) :
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

*/


