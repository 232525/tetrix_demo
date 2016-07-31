#include "ui_from_design.h"
#include <QApplication>
#include <QtWidgets>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    QApplication a(argc, argv);
    ui_from_design w;
    w.setFixedSize(450, 650);
    //添加背景图片--可以在类的构造函数中添加
//    w.setAutoFillBackground(true);
//    QPalette palette = w.palette();
//    palette.setBrush(QPalette::Window,
//                     QBrush(QPixmap(":/backPicture/back3.jpg").scaled(
//                                w.size(),
//                                Qt::IgnoreAspectRatio,
//                                Qt::SmoothTransformation))); // 使用平滑的缩放方式
//    w.setPalette(palette);
    w.setWindowTitle("俄罗斯方块");
    //添加俄罗斯方块图标
    QIcon ico(":/backPicture/tetrixIco.ico");
    w.setWindowIcon(ico);
    w.show();
    return a.exec();
}
