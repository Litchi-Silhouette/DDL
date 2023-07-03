#ifndef CONFIG_H
#define CONFIG_H

//定义一些全局参数，其他的参数由于可变所以在Mainwindow里定义为静态变量

#define Y_TOOL_UNIT_NUM 3.5  //关卡上方工具栏占?个单位 // 3.42:12 = 2:7
#define X_GRID_NUM 80      //x方向有?-2个单位 （边界也占两格）
#define Y_GRID_NUM 12      //y方向有?-2个单位 （边界也占两格）
#define MIN_KEYEVENT_INTERVAL 120  // 最短间隔为?毫秒
#define TIME_EVENT_INTERVAL 120 //time_event()触发间隔
#define START_DELAY_TIME 5500
#define DDL_LINE_WIDTH_CELL_SIZE_RATIO 0.5
#define DDL_LINE_BASE_V 0.9
#define EPS 0.001
// gamemap2
#define PLAYER_MAX_V_2 0.22
#define BOSS_MAX_V 0.3
#define BOSS_MIN_V 0.06
#define V_DACAY_TIME 2000.0
#define MOVE_EVENT_INTERVAL 30
// gamemap3
#define PLAYER_MAX_V_3 0.20
#define BULLET_BASE_V 0.12
#define TASKBUFF_BASE_V 0.04
#define TRACE_BULLET_ACCELERATION 0.03
#define BOSS_FLOAT_V 0.06


#include "level_page_base/levelwindow.h"
#include "level_page_base/Game.hpp"
#include "level_page_base/ddl_list.h"
#include "level_page_base/mylabel.h"
#include "level_page_base/live_bar.h"
#include "level_page_base/pause_button.h"
#include "level_page_base/pause_start_end.h"
#include "level_page_base/warning_icon.h"

#endif // CONFIG_H
