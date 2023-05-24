#include "utils.cpp"
#include "init.cpp"
#include "obstacle.cpp"
#include <QLayout>

int MainWindow::MOVE_UNIT = 0;
int MainWindow::CELL_SIZE = 0;
int MainWindow::X_BARRIER = 0;
int MainWindow::Y_BARRIER = 0;
int MainWindow::Y_TOOL_HEIGHT = 0;
int MainWindow::HEIGHT = 0;
int MainWindow::WIDTH = 0;

MainWindow::MainWindow(QString MapType,QWidget *parent)
    : QMainWindow(parent)
{

    showFullScreen();//调用resize event
    show();

    if (MapType == "1")
        pgamemap = new GameMapOne(this);
    else
        pgamemap = new GameMap(this);

    setStyleSheet("MainWindow{background-color: rgb(255, 255, 255);}");//设白色背景
    pgamemap->show();
    ptaskbuff_board = new QLabel(this);
    ptaskbuff_board->move(CELL_SIZE * 2.5,0);
    ptaskbuff_board->resize(CELL_SIZE * 2.5,CELL_SIZE * 2.5);
    ptaskbuff_board->setText("Empty task list");
    ptaskbuff_board->show();




}

MainWindow::~MainWindow(){delete pgamemap;}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    static qint64 lastKeyPressTime = 0;
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    QPoint cur = pgamemap->pfigure->pos();
    QSize size = pgamemap->pfigure->size();
    event->accept();

    switch(event->key())
    {
    case Qt::Key_A:
        cur.rx() -=MOVE_UNIT;break;
    case Qt::Key_W:
        cur.ry() -=MOVE_UNIT;break;
    case Qt::Key_D:
        cur.setX(cur.x()+MOVE_UNIT);break;
    case Qt::Key_S:
        cur.setY(cur.y()+MOVE_UNIT);break;
    default:
        return;
    }

    if(currentTime - lastKeyPressTime < MIN_KEYEVENT_INTERVAL) return;

    pgamemap->pfigure->move_in_grid(cur);
    lastKeyPressTime = currentTime;
}

void MainWindow::renew_taskbuff_board(TaskBuff * ptb){
    ptaskbuff_board->setText("名称 "+ptb->name+"\n文字 "+ptb->explanation);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{

    qDebug()<<"Resize event called";
    //QSize size = event->size();
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize size = screen->size();
    qDebug()<<"event size"<<size;
    double targetRatio = 16.0 / 9.0;
    double screenRatio = static_cast<double>(size.width()) / size.height();

    if (screenRatio > targetRatio)
    {
        // 高度撑满屏幕，宽度根据比例计算
        int width = static_cast<int>(size.height() * targetRatio);
        int x = (size.width() - width) / 2;
        setGeometry(x, 0, width, size.height());
        size.rwidth() = width;
    }
    else
    {

        // 宽度撑满屏幕，高度根据比例计算
        int height = static_cast<int>(size.width() / targetRatio);
        int y = (size.height() - height) / 2;
        setGeometry(0, y, size.width(), height);
        size.rheight() = height;
    }

    // 调整物品的大小
    //size = this->size();
    HEIGHT = size.height();
    WIDTH = size.width();
    MOVE_UNIT = size.height() / (Y_GRID_NUM + Y_TOOL_UNIT_NUM);
    CELL_SIZE = MOVE_UNIT;
    X_BARRIER = MOVE_UNIT;
    Y_BARRIER = MOVE_UNIT;
    Y_TOOL_HEIGHT = 4 * Y_BARRIER;
    qDebug()<<"CELL_SIZE = "<<CELL_SIZE;
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

}
