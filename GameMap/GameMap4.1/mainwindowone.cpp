#include "init.cpp"


MainWindowOne::MainWindowOne(Game & game,QWidget *parent) :
    MainWindow(game,parent,1)
{}

MainWindowOne::~MainWindowOne()
{}

void MainWindowOne::keyPressEvent(QKeyEvent* event)
{
    if(pgamemap->paused) return;
    static qint64 lastKeyPressTime = 0;
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();

    QPoint cur = pgamemap->pfigure->pos();
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

    if(currentTime - lastKeyPressTime < GameMapOne::MIN_KEYEVENT_INTERVAL) return;
    pgamemap->pfigure->move_in_grid(cur);
    lastKeyPressTime = currentTime;
}
