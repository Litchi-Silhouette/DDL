#ifndef FIGURE_H
#define FIGURE_H

#include <config.h>
#include <QWidget>
#include <QString>
#include <QLabel>


namespace Ui {
class Figure;
}

class GameMap;

class Figure : public QLabel
{
    Q_OBJECT

public:
    bool fixed;
    GameMap * parent_gamemap;
    explicit Figure(GameMap *parent = nullptr);
    ~Figure();
    void embed_image(QString path);
    void move_in_grid(const QPoint & pos);

private:
    Ui::Figure *ui;
};

#endif // FIGURE_H
