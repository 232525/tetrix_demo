#include "game_area_frame.h"
#include <QtWidgets>

game_area_frame::game_area_frame(QWidget *parent)
    : QFrame(parent)
{
    //next_area_frame界面初始化
    this->next_area = new next_area_frame(parent);
    this->next_area->setObjectName(QStringLiteral("next_area"));
    this->next_area->setFrameStyle(QFrame::Panel | QFrame::Raised);
    this->next_area->setGeometry(QRect(318, 50, 125, 125));
    this->next_area->update();
    //难度选择按钮的初始化
    levelBox = new QComboBox(parent);
    levelBox->setObjectName(QStringLiteral("level"));
    levelBox->setGeometry(QRect(318, 205, 128, 31));
    //设置Item的间距
    levelBox->setStyleSheet("QComboBox QAbstractItemView::item{height:20px;}");
    levelBox->setView(new QListView());
    //设置显示内容
    levelBox->addItem("Easy");
    levelBox->addItem("Normal");
    levelBox->addItem("Hard");
    //槽函数--难度改变
    connect(this->levelBox, SIGNAL(currentIndexChanged(int)), this, SLOT(change_level(int)));
    //默认难度为easy
    this->level = 800;

    //相关标记初始化
    this->isStart = false;
    this->isPause = false;
    this->isWaiting = true;
    this->now_Te = NULL;

    //状态标志位的初始化
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 10; j++)
            state[i][j] = 0;
}

void game_area_frame::set_NowTe()
{
    //设置方块绘制颜色--有问题！！！，已解决。。。
    this->now_Te = this->next_area->getTetrix();
    this->x = 120;
    this->y = 30;
    this->update();
    this->next_area->update();
}

//重载paintEvent函数，根据当前方块now_Te和当前位置信息（x,y）绘制
//在此处进行游戏是否结束的检测
void game_area_frame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);

    //需要修改
    if(!isStart){
        return;
    }
    //如果游戏结束，设置相关标记
    if(isEnd())
    {
        this->isStart = false;
        this->next_area->end();
        timer.stop();
        //将所有状态标记归零
        for(int i = 0; i < 20; i++)
            for(int j = 0; j < 10; j++)
                state[i][j] = 0;
        this->now_Te = NULL;
        QMessageBox::StandardButton reply;
        QString msg = "Score:" + QString::number(this->scoreAll,10)+"分";
        reply = QMessageBox::information(this, tr("得分："),
                                      msg,QMessageBox::Yes);
        return;
    }

    if(this->now_Te == NULL){
        this->set_NowTe();
    }

    tetrix *needDraw = this->now_Te;
    int nowX = this->x, nowY = this->y;
    int drawX = 0, drawY = 0;       //绘制坐标
    //绘制标记为1的位置、以及四个小方块
    for(int i = 19; i >= 0; i--)
    {
        for(int j = 0; j < 10; j++)
        {
            switch(state[i][j]){
            case 1:
                painter.setBrush(QBrush(QColor(255, 0, 0, 200), Qt::SolidPattern));
                break;
            case 2:
                painter.setBrush(QBrush(QColor(0, 229, 238, 200), Qt::SolidPattern));
                break;
            case 3:
                painter.setBrush(QBrush(QColor(255, 80, 0, 200), Qt::SolidPattern));
                break;
            case 4:
                painter.setBrush(QBrush(QColor(255, 215, 0, 200), Qt::SolidPattern));
                break;
            case 5:
                painter.setBrush(QBrush(QColor(0, 255, 150, 200), Qt::SolidPattern));
                break;
            case 6:
                painter.setBrush(QBrush(QColor(0, 100, 200, 200), Qt::SolidPattern));
                break;
            case 7:
                painter.setBrush(QBrush(QColor(238, 180, 180, 200), Qt::SolidPattern));
                break;
            default:
                break;
            }
            if(state[i][j] > 0){
                //根据状态值设置颜色并进行绘制
                drawX = j*30;
                drawY = i*30;
                painter.drawRect(drawX, drawY, 30, 30);
            }
        }
    }

    switch(this->now_Te->getname()){
    case 1:
        painter.setBrush(QBrush(QColor(255, 0, 0, 200), Qt::SolidPattern));
        break;
    case 2:
        painter.setBrush(QBrush(QColor(0, 229, 238, 200), Qt::SolidPattern));
        break;
    case 3:
        painter.setBrush(QBrush(QColor(255, 80, 0, 200), Qt::SolidPattern));
        break;
    case 4:
        painter.setBrush(QBrush(QColor(255, 215, 0, 200), Qt::SolidPattern));
        break;
    case 5:
        painter.setBrush(QBrush(QColor(0, 255, 150, 200), Qt::SolidPattern));
        break;
    case 6:
        painter.setBrush(QBrush(QColor(0, 100, 200, 200), Qt::SolidPattern));
        break;
    case 7:
        painter.setBrush(QBrush(QColor(238, 180, 180, 200), Qt::SolidPattern));
        break;
    }
    for(int i =  0; i < 4; i++)
    {
        drawX = nowX + 30*(needDraw->getX(i));
        drawY = nowY + 30*(needDraw->getY(i));
        painter.drawRect(drawX, drawY, 30, 30);
    }
    painter.end();
}

//重载keyPressEvent函数
void game_area_frame::keyPressEvent(QKeyEvent *event)
{
    if(!isStart)
    {
        QFrame::keyPressEvent(event);
        if(event->key() == Qt::Key_Space)
            this->start_game();
        return;
    }
    switch (event->key()) {     //需要添加头文件QtWidgets.h
    case Qt::Key_Left:
        tryMove(this->x - 30, this->y);
        break;
    case Qt::Key_Right:
        tryMove(this->x + 30, this->y);
        break;
    case Qt::Key_Up:
        //判断是否越界
        this->now_Te->rotate(this->x, this->y);
        //还要进行碰撞检测，不能旋转的话需要旋转三次变为原样
        if(!tryMove(this->x, this->y))
        {
            this->now_Te->rotate(this->x, this->y);
            this->now_Te->rotate(this->x, this->y);
            this->now_Te->rotate(this->x, this->y);
        }
        break;
    case Qt::Key_Down:
        this->tryMove(x, y+30);
        this->down();
        break;
    case Qt::Key_Space:
        this->pause_game();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void game_area_frame::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaiting == true) {
            isWaiting = false;
            this->set_NowTe();
            //表示将落下一个新的方块
            timer.start(timeoutTime(), this);
        } else {
            this->down();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

bool game_area_frame::isEmpty(int x, int y)
{
    int x1 = x/30;
    int y1 = y/30;
    //为空返回true
    if(state[y1][x1] == 0)
        return true;
    else
        return false;
}

//移动时进行碰撞检测
bool game_area_frame::tryMove(int newX, int newY)
{
    for(int i = 0; i < 4; i++)
    {
        int x = newX+30*(this->now_Te->getX(i));
        int y = newY+30*(this->now_Te->getY(i));
        if(x < 0 || x >= 300 || y < 0 || y >= 600){
            return false;
        }
        if(!isEmpty(x, y)){
            return false;
        }
    }
    //移动后更改当前位置
    this->x = newX;
    this->y = newY;
    //重绘
    update();
    return true;
}

//下移
void game_area_frame::down()
{
    //下移失败--将此时位置标志为1
    if(!this->tryMove(this->x, this->y+30))
    {
        //判断是否应该占位
        int sx, sy;
        for(int i = 0; i < 4; i++)
        {
            sx = this->x+30*this->now_Te->getX(i);
            sy = this->y+30*this->now_Te->getY(i);
            if(isEmpty(sx, sy))
                state[sy/30][sx/30] = this->now_Te->getname();
            else
                break;
        }
        this->deLine(this->y+30*this->now_Te->minY());
        if(this->isWaiting != true)
            this->set_NowTe();
    }
}
//消行计分
void game_area_frame::deLine(int y)
{
    int line = y/30;
    bool flag[4];
    int lineCnt = 4;
    //俄罗斯方块一次最多消去4行，得到四行的状态，即利用flag标志该行是否应该被消除
    for(int i = 0; i < 4; i++)
    {
        //如果越界
        flag[i] = true;
        if(line+i > 19){
            lineCnt--;
            continue;
        }
        for(int j = 0; j < 10; j++)
        {
            //有一个位置点为空则将flag置为false并退出判断
            if(state[line+i][j] == false){
                flag[i] = false;
                lineCnt--;
                break;
            }
        }
    }
    //进行消行处理--有问题(疑似已经解决)
    for(int i = 0; i < 4; i++)
    {
        //越界直接退出循环
        if(line+i > 19)
            break;
        //标志为真则消行--状态标识下移
        if(flag[i] == true)
        {
            for(int j = line+i; j >= 0; j--)
            {
                if(j==0)
                {
                    for(int k = 0; k < 10; k++)
                        state[0][k] = 0;
                    timer.start(timeoutTime(), this);
                }
                else
                {

                    for(int k = 0; k < 10; k++)
                    {
                        state[j][k] = state[j-1][k];
                    }
                }
            }
        }
    }
    //返回计分
    if(lineCnt > 0)
    {
        this->scoreAll += lineCnt*15-5;
        emit add_score(scoreAll);
    }
}

void game_area_frame::change_level(int level)
{
    //测试
    QString levelName = levelBox->itemText(level);
    if(levelName == "Easy"){
        this->level = 800;
    }
    else if(levelName == "Normal"){
        this->level = 500;
    }
    else if(levelName == "Hard"){
        this->level = 200;
    }
    timer.stop();
    if(this->isStart == true)
        timer.start(timeoutTime(), this);
    this->setFocus();
}

//游戏开始、暂停、结束信号函数
void game_area_frame::start_game()
{
    if(this->isStart == true)
    {
        for(int i = 0; i < 20; i++)
            for(int j = 0; j < 10; j++)
                state[i][j] = 0;
    }
    this->isStart = true;
    this->next_area->setStart();
    this->isWaiting = false;
    this->set_NowTe();
    this->scoreAll = 0;
    emit add_score(scoreAll);
    timer.start(timeoutTime(), this);
    this->update();
    this->next_area->update();
}

void game_area_frame::pause_game()
{
    if(!isStart)
        return;
    isPause = !isPause;
    if(isPause)
        timer.stop();
    else
        timer.start(timeoutTime(), this);
    update();
}

//程序结束
bool game_area_frame::isEnd()
{
    int fx = 120, fy = 30;
    int tx, ty;
    for(int i = 0; i < 4; i++)
    {
        tx = fx + 30*this->now_Te->getX(i);
        ty = fy + 30*this->now_Te->getY(i);
        //如果位置被占则返回程序结束
        if(ty >= 0 && state[ty/30][tx/30] > 0)
            return true;
    }
    return false;
}
