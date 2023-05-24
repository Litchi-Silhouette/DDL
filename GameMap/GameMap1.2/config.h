#ifndef CONFIG_H
#define CONFIG_H

//定义一些全局参数，其他的参数由于可变所以在Mainwindow里定义为静态变量

#define Y_TOOL_UNIT_NUM 4  //关卡上方工具栏占?个单位
#define X_GRID_NUM 40      //x方向有?-2个单位 （边界也占两格）
#define Y_GRID_NUM 11      //y方向有?-2个单位 （边界也占两格）
#define MIN_KEYEVENT_INTERVAL 100  // 最短间隔为?毫秒
#define TIME_EVENT_INTERVAL 50 //time_event()触发间隔



#endif // CONFIG_H
