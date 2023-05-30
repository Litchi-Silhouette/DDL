#include "ddl_list.h"
#include <QLayout>
#include <QTimer>

DDL_List::DDL_List(QWidget *parent, QHash<int , QListWidgetItem*>* _all,
                   QHash<QListWidgetItem*, task_info>* _task, QHash<QListWidgetItem*, task_info>* _buff)
    : QWidget{parent}, taskitems(_task), buffitems(_buff), allitems(_all)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);

    title = new MyLabel(this, "任务");
    title->setMinimumSize(30,30);
    title->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    finish = new MyLabel(this);
    finish->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    set_ini_task(0,0);

    QString temp = "QListWidget{background: rgba(220,220,220,0.6); border:0px;border-radius:5px}"
            "QListWidget::item{background:rgba(220,220,220,0.6);height:40px;border:1px solid gray;border-radius:5px}"
            "QListWidget::item:hover{background:rgba(210,210,210,1);}"
            "QListWidget::item:selected{border-width:3;color:black;background:rgba(220,220,220,0.6);}"
            "QListWidget::item:selected:active{border-width:3;color:black;background:rgba(220,220,220,0.6);}";

    QFont cur("Microsoft Yi Baiti",18,QFont::Bold);
    tasklist = new QListWidget(this);
    tasklist->setStyleSheet(temp);
    tasklist->setFont(cur);
    tasklist->setSpacing(5);
    tasklist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tasklist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tasklist->setFocusPolicy(Qt::NoFocus);
    tasklist->setIconSize(QSize(20,20));
    connect(tasklist, &QListWidget::itemClicked, this,&DDL_List::task_click);

    bufflist = new QListWidget(this);
    bufflist->setStyleSheet(temp);
    bufflist->setSpacing(3);
    bufflist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(bufflist, &QListWidget::itemClicked, this,&DDL_List::buff_click);
    bufflist->setViewMode(QListView::IconMode);
    bufflist->setFocusPolicy(Qt::NoFocus);
    bufflist->setMinimumSize(50,30);
    bufflist->setIconSize(QSize(18,18));

    name = new QLabel(" Escaping!", this);
    name->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    icon = new QLabel(this);
    icon->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    info = new QLabel(this);
    info->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    clear();

    auto left = new QGridLayout;
    auto up = new QHBoxLayout;
    auto bottom = new QHBoxLayout;
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
    left->addLayout(up,0,0,1,2);
    left->addWidget(tasklist,1,1,1,1);
    left->setColumnStretch(0,1);
    left->setColumnStretch(1,10);
    left->setRowStretch(0,1);
    left->setRowStretch(1,3);

    QWidget* _1 = new QWidget(this);
    QWidget* _2 = new QWidget(this);
    bottom->addWidget(_1);
    bottom->addWidget(bufflist);
    bottom->addWidget(_2);
    bottom->setStretchFactor(_1,1);
    bottom->setStretchFactor(bufflist,5);
    bottom->setStretchFactor(_2,3);

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
    right->addLayout(bottom);
    right->setStretchFactor(right_up,1);
    right->setStretchFactor(info,3);
    right->setStretchFactor(bottom,1);

    main_lay->setSpacing(10);
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
    update_finish(f);
}

void DDL_List::update_finish(const int x){
    finished = x;
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


void DDL_List::add_task(const QPixmap& icon, const QString& name,
                        const QString& info, const int index, const bool isRed)
{
    QIcon cur(icon);
    cur.addPixmap(icon, QIcon::Selected);
    QListWidgetItem* temp = new QListWidgetItem(cur,name);
    temp->setSizeHint(QSize(30,30));
    tasklist->insertItem(0,temp);
    taskitems->insert(temp, task_info(icon, name, info, isRed));
    allitems->insert(index, temp);
}

void DDL_List::add_buff(const QPixmap& icon, const QString& name,
                        const QString& info, const int index, const bool isRed)
{
    QIcon cur(icon);
    cur.addPixmap(icon, QIcon::Selected);
    QListWidgetItem* temp = new QListWidgetItem(cur,"");
    temp->setSizeHint(QSize(24,24));
    bufflist->insertItem(0,temp);
    buffitems->insert(temp, task_info(icon, name, info, isRed));
    allitems->insert(index, temp);
}

void DDL_List::remove_task(const int index)
{
    auto& cur = allitems->find(index).value();
    taskitems->remove(cur);
    tasklist->removeItemWidget(cur);
    delete cur;
    allitems->remove(index);
    showIni();
}

void DDL_List::remove_buff(const int index)
{
    auto& cur = allitems->find(index).value();
    buffitems->remove(cur);
    bufflist->removeItemWidget(cur);
    delete cur;
    allitems->remove(index);
    showIni();
}

void DDL_List::set_info(QListWidgetItem* cur, bool is_buff, bool is_nor)
{
    auto curTFont = title->font();
    auto curFFont = curTFont;
    if(is_nor)
    {
        QPalette pe = title->palette();
        name->setPalette(pe);
        info->setPalette(pe);
    }
    else
    {
        QPalette pe = title->palette();
        pe.setColor(QPalette::WindowText,Qt::red);
        name->setPalette(pe);
        info->setPalette(pe);
    }
    curFFont.setBold(false);
    if(is_buff)
    {
        auto& temp = buffitems->find(cur).value();
        icon->setPixmap(QIcon(temp.geticon()).pixmap(name->size(),Qt::KeepAspectRatio));
        name->setFont(curTFont);
        name->setText(QString(" %1").arg(temp.getname()));
        info->setFont(curFFont);
        info->setText(temp.getinfo());
    }
    else
    {
        auto& temp = taskitems->find(cur).value();
        icon->setPixmap(QIcon(temp.geticon()).pixmap(name->size(),Qt::KeepAspectRatio));
        name->setFont(curTFont);
        name->setText(QString(" %1").arg(temp.getname()));
        info->setFont(curFFont);
        info->setText(temp.getinfo());
    }
}

void DDL_List::buff_click(QListWidgetItem *item)
{
    bool red = buffitems->find(item).value().getRed();
    set_info(item,true,!red);
    clearTaskSelected();
}

void DDL_List::task_click(QListWidgetItem *item)
{
    bool red = taskitems->find(item).value().getRed();
    set_info(item,false,!red);
    clearBuffSelected();
}

void DDL_List::showBuff(const int index){
    auto& cur = allitems->find(index).value();
    bool red = buffitems->find(cur).value().getRed();
    set_info(cur,true,!red);
    clearBuffSelected();
    clearTaskSelected();
}

void DDL_List::showTask(const int index){
    auto& cur = allitems->find(index).value();
    bool red = taskitems->find(cur).value().getRed();
    set_info(cur,false,!red);
    clearBuffSelected();
    clearTaskSelected();
}

void DDL_List::changeTaskColour(const int index, bool red){
    auto& cur = allitems->find(index).value();
    taskitems->find(cur).value().getRed() = red;
}

void DDL_List::changeBuffColour(const int index, bool red){
    auto& cur = allitems->find(index).value();
    buffitems->find(cur).value().getRed() = red;
}

void DDL_List::clearTaskSelected(){
    auto temp = tasklist->selectedItems();
    for(auto& i:temp)
        i->setSelected(false);
}

void DDL_List::clearBuffSelected(){
    auto temp = bufflist->selectedItems();
    for(auto& i:temp)
        i->setSelected(false);
}

void DDL_List::clear(){
    tasklist->clear();
    bufflist->clear();
    taskitems->clear();
    buffitems->clear();
    showIni();
    finished = 0;
}

void DDL_List::showIni(){
    name->setText(" Easecaping!");
    QPixmap ini(":/page/level_image/icon_w.png");
    icon->setPixmap(ini.scaled(name->size(),Qt::KeepAspectRatio));
    info->setText("");
    clearBuffSelected();
    clearTaskSelected();
}
