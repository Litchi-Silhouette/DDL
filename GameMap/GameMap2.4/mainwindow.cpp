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
int MainWindow::MAP_HEIGHT = 0;

MainWindow::MainWindow(QWidget *parent, int level)
    : LevelWindow(parent,level)
{
    setMapVisible(false);
    showFullScreen();//调用resize event

    switch(level){
    case 1:
        pgamemap = new GameMapOne(this);break;
    case 2:
        pgamemap = new GameMapTwo(this);break;
    default:
        pgamemap = new GameMap(this);break;
    }


    setStyleSheet("MainWindow{background-color: rgb(255, 255, 255);}");//设白色背景
    pgamemap->show();
    ptaskbuff_board = new QLabel(this);
    ptaskbuff_board->move(CELL_SIZE * 2.5,0);
    ptaskbuff_board->resize(CELL_SIZE * 2.5,CELL_SIZE * 2.5);
    ptaskbuff_board->setText("Empty task list");
    ptaskbuff_board->show();

}

MainWindow::~MainWindow(){delete pgamemap;}



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
    Y_TOOL_HEIGHT = Y_TOOL_UNIT_NUM * Y_BARRIER;
    MAP_HEIGHT = HEIGHT - Y_TOOL_HEIGHT;
    qDebug()<<"CELL_SIZE = "<<CELL_SIZE;
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

}

void MainWindow::add_taskbuff(TaskBuff * ptb){

    if(ptb->type == "Task" or ptb->type == "task")
        LevelWindow::add_task(ptb->img_path,ptb->name,ptb->explanation,ptb->id,ptb->missed);
    else if(ptb->type == "Buff" or ptb->type == "buff" or ptb->type == "Auto" or ptb->type == "auto")
        LevelWindow::add_buff(ptb->img_path,ptb->name,ptb->explanation,ptb->id,ptb->missed);
    else
        qDebug()<<"Error in MainWindow::add_taskbuff : not Task or Buff "<<ptb->name;

}
void MainWindow::show_taskbuff(TaskBuff * ptb){
    //QPixmap icon(ptb->img_path);
    if(ptb->type == "Task" or ptb->type == "task")
        LevelWindow::showTask(ptb->id);
    else if(ptb->type == "Buff" or ptb->type == "buff" or ptb->type == "Auto" or ptb->type == "auto")
        LevelWindow::showBuff(ptb->id);
    else
        qDebug()<<"Error in MainWindow::show_taskbuff : not Task or Buff "<<ptb->name;
}
void MainWindow::remove_taskbuff(TaskBuff * ptb){
    //QPixmap icon(ptb->img_path);
    if(ptb->type == "Task" or ptb->type == "task")
        LevelWindow::remove_task(ptb->id);
    else if(ptb->type == "Buff" or ptb->type == "buff" or ptb->type == "Auto" or ptb->type == "auto")
        LevelWindow::remove_buff(ptb->id);
    else
        qDebug()<<"Error in MainWindow::remove_taskbuff : not Task or Buff "<<ptb->name;
}

void MainWindow::changeGameProcess(bool pause_or_continue)
{
    LevelWindow::changeGameProcess(pause_or_continue);
    if(pause_or_continue)
        pgamemap->pause_game();
    else
        pgamemap->continue_game();

}

void MainWindow::missed_task_drop_live(TaskBuff * ptb, const int & drop_live)
{
    live -= drop_live; if(live < 0)live = 0;
    LevelWindow::update_live();
    if(ptb->type == "Task" || ptb->type == "task")
        LevelWindow::update_List();
}

void MainWindow::reset(){
    resettask(0,TaskBuff::total_task);
    set_change(1.0,0.0);
}
void MainWindow::update_warning(const double & distance){ // range[0,1]
    set_size(1.0 - distance);
    if(distance < 0.3){
        set_mode(2);
    }else if (distance > 0.9){
        set_mode(0);
    }else{
        set_mode(1);
    }
}

