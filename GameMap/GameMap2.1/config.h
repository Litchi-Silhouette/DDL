#ifndef CONFIG_H
#define CONFIG_H

//定义一些全局参数，其他的参数由于可变所以在Mainwindow里定义为静态变量

#define Y_TOOL_UNIT_NUM 5.14  //关卡上方工具栏占?个单位 // 5.14:12 = 3:7
#define X_GRID_NUM 80      //x方向有?-2个单位 （边界也占两格）
#define Y_GRID_NUM 12      //y方向有?-2个单位 （边界也占两格）
#define MIN_KEYEVENT_INTERVAL 40  // 最短间隔为?毫秒
#define TIME_EVENT_INTERVAL 100 //time_event()触发间隔
#define DDL_LINE_SPEED_PER_S 30
#define START_DELAY_TIME 5500
#define DDL_LINE_WIDTH_CELL_SIZE_RATIO 0.5

#include "level_page_base/levelwindow.h"
#include "level_page_base/Game.h"
#include "level_page_base/ddl_list.h"
#include "level_page_base/mylabel.h"
#include "level_page_base/live_bar.h"
#include "level_page_base/pause_button.h"
#include "level_page_base/set_pausedialog.h"
#include "level_page_base/warning_icon.h"

#endif // CONFIG_H
