#include "ui_from_design.h"
#include <QtWidgets>

ui_from_design::ui_from_design()
{
    setupUi(this);

    //添加背景图片
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/backPicture/back3.jpg").scaled(
                                this->size(),
                                Qt::IgnoreAspectRatio,
                                Qt::SmoothTransformation))); // 使用平滑的缩放方式
    this->setPalette(palette);

    //将槽函数和组件连接起来
    connect(exitB, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(startB, SIGNAL(clicked()), game_area, SLOT(start_game()));
    connect(pauseB, SIGNAL(clicked()), game_area, SLOT(pause_game()));
    //槽函数--计分功能
    connect(game_area, SIGNAL(add_score(int)), score, SLOT(display(int)));
}
