#include "next_area_frame.h"

next_area_frame::next_area_frame(QWidget *parent) :
    QFrame(parent)
{
    //创建实例时产生 一个随机的方块
    this->nextTe = new tetrix();
    this->isStart = false;
}

void next_area_frame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);

    if(!isStart)
    {
        for(int i = 0; i < 125; i++)
            for(int j = 0; j < 125; j++)
            {
                painter.drawRect(i, j, 0, 0);
            }
    }
    else
    {
        int x, y;
        switch(this->nextTe->getname()){
        case 1:
            x = 62;
            y = 45;
            painter.setBrush(QBrush(QColor(255, 0, 0, 200), Qt::SolidPattern));
            break;
        case 2:
            x = 32;
            y = 75;
            painter.setBrush(QBrush(QColor(0, 229, 238, 200), Qt::SolidPattern));
            break;
        case 3:
            x = 62;
            y = 65;
            painter.setBrush(QBrush(QColor(255, 80, 0, 200), Qt::SolidPattern));
            break;
        case 4:
            x = 47;
            y = 40;
            painter.setBrush(QBrush(QColor(255, 215, 0, 200), Qt::SolidPattern));
            break;
        case 5:
            x = 47;
            y = 60;
            painter.setBrush(QBrush(QColor(0, 255, 150, 200), Qt::SolidPattern));
            break;
        case 6:
            x = 32;
            y = 32;
            painter.setBrush(QBrush(QBrush(QColor(0, 100, 200, 200), Qt::SolidPattern)));
            break;
        case 7:
            x = 47;
            y = 62;
            painter.setBrush(QBrush(QColor(238, 180, 180, 200), Qt::SolidPattern));
            break;
        }
        for(int i = 0; i < 4; i++)
        {
            painter.drawRect(x+30*this->nextTe->getX(i), y+30*this->nextTe->getY(i), 30, 30);
        }
        painter.end();
    }
}
