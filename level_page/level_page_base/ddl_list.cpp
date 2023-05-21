#include "ddl_list.h"
#include <QLayout>
#include <QTimer>

DDL_List::DDL_List(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    title = new MyLabel(this, "任务：");
    title->setMinimumSize(30,30);
    title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    finish = new MyLabel(this);
    finish->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    set_ini_task(0,0);

    QString temp = "QListWidget{background: rgba(200,200,200,0.6); border:0px;border-radius:5px}"
            "QListWidget::item{background:rgba(200,200,200,0.6);height:40px;border:1px solid gray;border-radius:5px}"
            "QListWidget::item:hover{background:rgba(200,200,200,1);}"
            "QListWidget::item:selected{border-width:3;color:black}";
    QFont cur("Microsoft Yi Baiti",18,QFont::Bold);
    tasklist = new QListWidget(this);
    tasklist->setStyleSheet(temp);
    tasklist->setFont(cur);
    tasklist->setSpacing(5);
    tasklist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tasklist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    connect(tasklist, &QListWidget::itemClicked, this,&DDL_List::task_click);
    bufflist = new QListWidget(this);
    bufflist->setStyleSheet(temp);
    bufflist->setSpacing(3);
    bufflist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(bufflist, &QListWidget::itemClicked, this,&DDL_List::buff_click);
    bufflist->setViewMode(QListView::IconMode);
    bufflist->setMinimumSize(50,30);
    taskitems.clear();
    buffitems.clear();

    name = new MyLabel(this,"：Easecaping!");
    name->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    QPixmap test(":/page/level_image/icon_w.png");
    icon = new QLabel(this);
    icon->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    icon->setPixmap(test.scaled(name->size(),Qt::KeepAspectRatio));
    info = new QLabel(this);
    info->setAlignment(Qt::AlignTop|Qt::AlignHCenter);

    auto left = new QGridLayout;
    auto up = new QHBoxLayout;
    auto right = new QVBoxLayout;
    auto right_up = new QHBoxLayout;
    auto main_lay = new QHBoxLayout;

    up->setSpacing(0);
    up->setContentsMargins(0,0,0,0);
    up->addWidget(title);
    up->addWidget(finish);
    up->setStretchFactor(title,1);
    up->setStretchFactor(finish,2);

    left->setSpacing(5);
    left->setContentsMargins(0,0,0,0);
    left->addLayout(up,0,0,1,3);
    left->addWidget(tasklist,1,1,1,2);
    left->setColumnStretch(0,1);
    left->setColumnStretch(1,1);
    left->setColumnStretch(2,4);
    left->setRowStretch(0,1);
    left->setRowStretch(1,3);

    right_up->setContentsMargins(0,0,0,0);
    right_up->setSpacing(0);
    right_up->addWidget(icon,Qt::AlignRight|Qt::AlignBottom);
    right_up->addWidget(name);
    right_up->setStretchFactor(icon,1);
    right_up->setStretchFactor(name,3);
    right->setContentsMargins(0,0,0,0);
    right->setSpacing(5);
    right->addLayout(right_up);
    right->addWidget(info);
    right->addWidget(bufflist);
    right->setStretchFactor(right_up,1);
    right->setStretchFactor(info,3);
    right->setStretchFactor(bufflist,1);

    main_lay->setSpacing(5);
    main_lay->setContentsMargins(0,0,0,0);
    main_lay->addLayout(left);
    main_lay->addLayout(right);
    main_lay->setStretchFactor(left,1);
    main_lay->setStretchFactor(right,1);
    setLayout(main_lay);
}

void DDL_List::set_ini_task(int f, int a)
{
    finished = f;
    all_task = a;
    update_finish();
}

void DDL_List::update_finish(){
    finish->setText(QString("(进度：%1/%2)").arg(finished).arg(all_task));
}

DDL_List::~DDL_List()
{
    delete tasklist;
    delete bufflist;
    delete title;
    delete finish;
    delete name;
    delete icon;
    delete info;
}


void DDL_List::add_task(const QIcon icon, const QString name, const QString info)
{
    QListWidgetItem* temp = new QListWidgetItem(icon,name,tasklist);
    tasklist->addItem(temp);
    taskitems[temp] = info;
}

void DDL_List::add_buff(const QIcon icon, const QString name, const QString info)
{
    QListWidgetItem* temp = new QListWidgetItem(bufflist);
    temp->setSizeHint(QSize(24,24));
    temp->setIcon(icon.pixmap(QSize(11,11)));
    bufflist->addItem(temp);
    buffitems[temp] = std::make_pair(name, info);
}

void DDL_List::remove_task(QListWidgetItem* cur)
{
    taskitems.remove(cur);
    tasklist->removeItemWidget(cur);
}

void DDL_List::remove_buff(QListWidgetItem* cur)
{
    buffitems.remove(cur);
    bufflist->removeItemWidget(cur);
}

void DDL_List::set_info(QListWidgetItem* cur, bool is_buff)
{
    if(is_buff)
    {
        icon->setPixmap(cur->icon().pixmap(icon->size()));
        name->setText(QString("：%1").arg(buffitems[cur].first));
        info->setText(buffitems[cur].second);
    }else{
        icon->setPixmap(cur->icon().pixmap(icon->size()));
        name->setText(QString("：%1").arg(cur->text()));
        info->setText(taskitems[cur]);
    }
}

void DDL_List::buff_click(QListWidgetItem *item)
{
    set_info(item,true);
}

void DDL_List::task_click(QListWidgetItem *item)
{
    set_info(item,false);
}

void DDL_List::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    icon_height = title->height()-20;
    info->setFont(name->font());
}
