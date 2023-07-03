#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class TipDialog; }
QT_END_NAMESPACE

class TipDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(int tmpHeight READ tmpHeight WRITE setTmpHeight NOTIFY tmpHeightChanged)

public:
    TipDialog(int level, QWidget *parent = nullptr);
    ~TipDialog();
    int tmpHeight(){
        return height();
    }
    void setTmpHeight(int h){
        setFixedHeight(h);
        emit tmpHeightChanged();
    }
protected:
    void showEvent(QShowEvent*);
    void closeGradually();
private slots:
    void on_pushButton_clicked();

signals:
    void closeEnd();
    void tmpHeightChanged();
private:
    void getText(int);

    Ui::TipDialog *ui;
    int heightFinal;
    QPropertyAnimation *showAnimation;
    QPropertyAnimation *closeAnimation;
    QPropertyAnimation *tipShow;
    QPropertyAnimation *titleShow;
    QGraphicsOpacityEffect* tipOp;
    QGraphicsOpacityEffect* titleOp;
};
#endif // TIPDIALOG_H
