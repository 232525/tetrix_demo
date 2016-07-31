#ifndef GAME_AREA_FRAME_H
#define GAME_AREA_FRAME_H

#include <QFrame>
#include <QWidget>
#include <QPainter>
#include <QtCore>
#include <QPointer>
#include <QComboBox>
#include<QMessageBox>
#include "tetrix.h"
#include "next_area_frame.h"

//游戏运行界面类，应该包含在该区域内对方块处理的函数，包括移动、翻转消行等
class game_area_frame : public QFrame
{
    Q_OBJECT

public:
    tetrix *now_Te;             //当前方块
    game_area_frame(QWidget *parent = 0);

    //方块设置：设置当前方块，下一个方块
    void set_NowTe();

    //方块移动--tryMove函数中包含碰撞检测，如果无法移动则返回false，能移动返回true
    bool tryMove(int newX, int newY);
    void down();                                //向下运动
    void deLine(int y);                         //消行积分
    bool isEnd();                               //判断游戏是否应该结束

    //判断
    bool isEmpty(int x, int y);
signals:
    void add_score(int score);
public slots:
    void start_game();
    void pause_game();
    void change_level(int level);

protected:
    void paintEvent(QPaintEvent *event);       //绘制函数，绘制位置，绘制方块
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
private:
    next_area_frame *next_area;
    int state[20][10];         //状态标记，标记是否被方块所占以及是什么颜色
    int x, y;                   //当前方块所在位置
    int scoreAll;
    int level;
    QComboBox *levelBox;
    //暂停开始标志
    bool isStart;
    bool isPause;
    //定时器
    QBasicTimer timer;
    bool isWaiting;
    int timeoutTime(){return level;}
    Qt::GlobalColor penColor;
};

#endif // GAME_AREA_FRAME_H
