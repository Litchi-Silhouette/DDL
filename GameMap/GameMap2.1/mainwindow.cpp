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

MainWindow::MainWindow(QWidget *parent)
    : LevelWindow(parent,1)
{
    setMapVisible(false);
    qDebug()<<"______";
    showFullScreen();//调用resize event
    qDebug()<<"______";

    pgamemap = new GameMapOne(this);

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
    if(pgamemap->paused) return;
    static qint64 lastKeyPressTime = 0;
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    QPoint cur = pgamemap->pfigure->pos();
    QSize size = pgamemap->pfigure->size();
    //event->accept();

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
    QSize screen_size = screen->size();
    QSize size = event->size();
    qDebug()<<"event size"<<size<<" screen size "<<screen_size;
    double targetRatio = static_cast<double>(size.width()) / size.height();
    double screenRatio = static_cast<double>(screen_size.width()) / screen_size.height();

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

void MainWindow::add_taskbuff(TaskBuff * ptb){

    QPixmap icon(ptb->img_path);
    if(ptb->type == "Task" or ptb->type == "task")
        LevelWindow::add_task(icon,ptb->name,ptb->explanation,ptb->id);
    else if(ptb->type == "Buff" or ptb->type == "buff")
        LevelWindow::add_buff(icon,ptb->name,ptb->explanation,ptb->id);
    else
        qDebug()<<"Error in MainWindow::add_taskbuff : not Task or Buff "<<ptb->name;

}
void MainWindow::show_taskbuff(TaskBuff * ptb){
    //QPixmap icon(ptb->img_path);
    if(ptb->type == "Task" or ptb->type == "task")
        LevelWindow::showTask(ptb->id);
    else if(ptb->type == "Buff" or ptb->type == "buff")
        LevelWindow::showBuff(ptb->id);
    else
        qDebug()<<"Error in MainWindow::show_taskbuff : not Task or Buff "<<ptb->name;
}
void MainWindow::remove_taskbuff(TaskBuff * ptb){
    //QPixmap icon(ptb->img_path);
    if(ptb->type == "Task" or ptb->type == "task")
        LevelWindow::remove_task(ptb->id);
    else if(ptb->type == "Buff" or ptb->type == "buff")
        LevelWindow::remove_buff(ptb->id);
    else
        qDebug()<<"Error in MainWindow::remove_taskbuff : not Task or Buff "<<ptb->name;
}

void MainWindow::changeGameProcess(bool pause_or_continue){

    LevelWindow::changeGameProcess(pause_or_continue);
    if(pause_or_continue)
        pgamemap->pause_game();
    else
        pgamemap->continue_game();

}
