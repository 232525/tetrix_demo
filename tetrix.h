#ifndef TETRIX_H
#define TETRIX_H

#include <QFrame>
#include <QPointer>

class tetrix
{
private:
    int shape[4][4][2];
    char shape_name;
    int rotate_cnt;
public:
    tetrix(char shape_name);
    tetrix();
    int getname();
    void rotate(int x, int y);
    //返回方块的相对位置信息
    int getX(int n) const;
    int getY(int n) const;
    //检测方块的边界，用于碰撞检测
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;
};

#endif // TETRIX_H
