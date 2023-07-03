#include "init.cpp"


class DDL_Line : public QLabel
{
public:
    GameMap * parent_gamemap;
    double left_barrier;
    double speed_per_ms;
    int width;

    DDL_Line(GameMap * parent): QLabel((QWidget *)parent){
        parent_gamemap = parent;
        width = MainWindow::CELL_SIZE * DDL_LINE_WIDTH_CELL_SIZE_RATIO;
        left_barrier = 0.0;

        speed_per_ms = MainWindow::CELL_SIZE * DDL_LINE_BASE_V / 1000.0;

        setGeometry(0, 0, width, MainWindow::CELL_SIZE * Y_GRID_NUM);
        setText("D\nE\nA\nD\nL\nI\nN\nE");
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);setPalette(pa);
        QFont ft;
        ft.setPointSize(20.0 / 58.0 * MainWindow::CELL_SIZE);
        setContentsMargins(30.0 / 58.0 * MainWindow::CELL_SIZE,0,0,0);
        ft.setItalic(true);
        setAlignment(Qt::AlignRight);
        setAlignment(Qt::AlignVCenter);
        setFont(ft);
        setStyleSheet("QLabel{background-color:rgb(0,0,0);}");

        qDebug()<<"ddlline constructor called geo "<<geometry();
    }




};
