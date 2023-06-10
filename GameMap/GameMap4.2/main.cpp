#include "init.cpp"
#include "obstacle.cpp"


Game statics;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow *pwindow = new MainWindowOne(statics);

    qDebug()<<"MainWindow size "<<pwindow->height()<<" "<<pwindow->width();
    pwindow->show();


    return a.exec();
}
