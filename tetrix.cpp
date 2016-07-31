#include "tetrix.h"
#include <QtWidgets>

//四维数组，第一维表示7种方块；第二维表示方块旋转四个方向；第三维表示方块的四个小方块；第四维为形状的相对描述
//七种情况如下：
/*
 * (1) [][][][]
 *
 * (2) []                       (3)   []
 *     []                             []
 *     [][]                         [][]
 *
 * (4)  [][]                    (5) [][]
 *    [][]                            [][]
 *
 * (6) [][]                     (7)   []
 *     [][]                         [][][]
 *
*/

static const int shape_all[7][4][4][2] = {
/*I*/    { { { -2,  0 }, { -1,  0 }, {  0,  0 }, {  1,  0 } },
           { {  0, -1 }, {  0, -2 }, {  0,  0 }, {  0,  1 } },
           { { -2,  0 }, { -1,  0 }, {  0,  0 }, {  1,  0 } },
           { {  0, -1 }, {  0, -2 }, {  0,  0 }, {  0,  1 } } },
/*L*/    { { {  0, -2 }, {  0, -1 }, {  0,  0 }, {  1,  0 } },
           { { -1,  0 }, {  0,  0 }, {  1,  0 }, {  1, -1 } },
           { { -1, -2 }, {  0, -2 }, {  0, -1},  {  0,  0 } },
           { { -1,  1 }, { -1,  0 }, {  0,  0 }, {  1,  0 } } },
/*J*/    { { {  0, -2 }, {  0, -1 }, {  0,  0 }, { -1,  0 } },
           { { -1,  0 }, {  0,  0 }, {  1,  0 }, {  1,  1 } },
           { {  1, -2 }, {  0, -2 }, {  0, -1 }, {  0,  0 } },
           { { -1, -1 }, { -1,  0 }, {  0,  0 }, {  1,  0 } } },
/*S*/    { { {  1,  0 }, {  0,  0 }, {  0,  1 }, { -1,  1 } },
           { {  0, -1 }, {  0,  0 }, {  1,  0 }, {  1,  1 } },
           { {  1,  0 }, {  0,  0 }, {  0,  1 }, { -1,  1 } },
           { {  0, -1 }, {  0,  0 }, {  1,  0 }, {  1,  1 } }},
/*Z*/    { { { -1, -1 }, {  0, -1 }, {  0,  0 }, {  1,  0 } },
           { { -1,  1 }, { -1,  0 }, {  0,  0 }, {  0, -1 } },
           { { -1, -1 }, {  0, -1 }, {  0,  0 }, {  1,  0 } },
           { { -1,  1 }, { -1,  0 }, {  0,  0 }, {  0, -1 } } },
/*O*/    { { {  0,  0 }, {  0,  1 }, {  1,  0 }, {  1,  1 } },
           { {  0,  0 }, {  0,  1 }, {  1,  0 }, {  1,  1 } },
           { {  0,  0 }, {  0,  1 }, {  1,  0 }, {  1,  1 } },
           { {  0,  0 }, {  0,  1 }, {  1,  0 }, {  1,  1 } } },
/*T*/    { { { -1,  0 }, {  1,  0 }, {  0,  0 }, {  0, -1 } },
           { {  0, -1 }, {  0,  1 }, {  0,  0 }, { -1,  0 } },
           { {  0,  0 }, {  0, -1 }, { -1, -1 }, {  1, -1 } },
           { {  0,  0 }, {  0, -1 }, {  0,  1 }, {  1,  0 } } }
};

tetrix::tetrix(char shape_name)
{
    this->shape_name = shape_name;
    this->rotate_cnt = 0;
    switch(shape_name)
    {
    case 'I':
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[0][i][j][k];
        break;
    case 'L':
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[1][i][j][k];
        break;
    case 'J':
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[2][i][j][k];
        break;
    case 'S':
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[3][i][j][k];
        break;
    case 'Z':
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[4][i][j][k];
        break;
    case 'O':
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[5][i][j][k];
        break;
    case 'T':
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[6][i][j][k];
        break;
    }
}

tetrix::tetrix(){
    int shapeNum = qrand()%7;
    this->rotate_cnt = 0;
    switch(shapeNum)
    {
    case 0:
        this->shape_name = 'I';
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[0][i][j][k];
        break;
    case 1:
        this->shape_name = 'L';
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[1][i][j][k];
        break;
    case 2:
        this->shape_name = 'J';
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[2][i][j][k];
        break;
    case 3:
        this->shape_name = 'S';
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[3][i][j][k];
        break;
    case 4:
        this->shape_name = 'Z';
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[4][i][j][k];
        break;
    case 5:
        this->shape_name = 'O';
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[5][i][j][k];
        break;
    case 6:
        this->shape_name = 'T';
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                for(int k = 0; k < 2; k++)
                    shape[i][j][k] = shape_all[6][i][j][k];
        break;
    }
}

int tetrix::getX(int n) const
{
    return this->shape[this->rotate_cnt][n][0];     //返回x相对位置
}

int tetrix::getY(int n) const
{
    return this->shape[this->rotate_cnt][n][1];     //返回y相对位置
}

int tetrix::minX() const
{
    int min = shape[rotate_cnt][0][0];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, shape[rotate_cnt][i][0]);
    return min;
}

int tetrix::maxX() const
{
    int max = shape[rotate_cnt][0][0];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, shape[rotate_cnt][i][0]);
    return max;
}

int tetrix::minY() const
{
    int min = shape[rotate_cnt][0][1];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, shape[rotate_cnt][i][1]);
    return min;
}

int tetrix::maxY() const
{
    int max = shape[rotate_cnt][0][1];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, shape[rotate_cnt][i][1]);
    return max;
}

//在此处进行旋转检测
void tetrix::rotate(int x, int y)
{
    int x_, y_;
    for(int i = 0; i < 4; i++)
    {
        x_ = x + shape[(rotate_cnt+1)%4][i][0]*30;
        y_ = y + shape[(rotate_cnt+1)%4][i][1]*30;
        if(x_ < 0 || x_ >= 300 || y_ < 0 || y_ >= 600)
            return;
    }
    rotate_cnt = (rotate_cnt+1)%4;
}

int tetrix::getname()
{
    switch(this->shape_name){
    case 'I':
        return 1;
        break;
    case 'L':
        return 2;
        break;
    case 'J':
        return 3;
        break;
    case 'S':
        return 4;
        break;
    case 'Z':
        return 5;
        break;
    case 'O':
        return 6;
        break;
    case 'T':
        return 7;
        break;
    }
}
