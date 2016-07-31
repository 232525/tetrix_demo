#ifndef NEXT_AREA_FRAME_H
#define NEXT_AREA_FRAME_H

#include "tetrix.h"
#include <QFrame>
#include <QPainter>

class next_area_frame : public QFrame
{
    Q_OBJECT
public:
    next_area_frame(QWidget *parent = 0);
    //随机产生下一个方块并将其作为返回值便于游戏界面接收
    void setStart(){this->isStart = true;}
    void end(){this->isStart = false; this->update();}
    void setTetrix(){this->nextTe = new tetrix();}
    tetrix* getTetrix(){
        tetrix *re = this->nextTe;
        setTetrix();
        return re;
    }
    void clearFrame();

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private:
    //下一个方块
    tetrix *nextTe;
    //标记是否开始，用来决定是否绘制下一方块
    bool isStart;
};

#endif // NEXT_AREA_FRAME_H
