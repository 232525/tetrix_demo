/********************************************************************************
** Form generated from reading UI file 'design.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGN_H
#define DESIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <QPointer>
#include <QComboBox>
#include <QListView>
#include "game_area_frame.h"
#include "next_area_frame.h"

QT_BEGIN_NAMESPACE

class Ui_All_Area
{
public:
    //按钮
    QPushButton *startB;
    QPushButton *pauseB;
    QPushButton *exitB;
    //游戏窗口和显示框
    game_area_frame *game_area;
    //分数窗口
    QLCDNumber *score;
    //显示信息
    QLabel *next_label;
    QLabel *level_label;
    QLabel *score_label;

    void setupUi(QWidget *All_Area)
    {
        if (All_Area->objectName().isEmpty())
            All_Area->setObjectName(QStringLiteral("All_Area"));
        All_Area->resize(450, 640);

        QSize size(98, 45);
        startB = new QPushButton(All_Area);
        startB->setObjectName(QStringLiteral("startB"));
        startB->setFocusPolicy(Qt::NoFocus);
        QPixmap startIcon(":/backPicture/start.png");
        startB->setIcon(startIcon);
        startB->setIconSize(size);
        startB->setGeometry(QRect(330, 390, 98, 45));

        pauseB = new QPushButton(All_Area);
        pauseB->setObjectName(QStringLiteral("pauseB"));
        pauseB->setFocusPolicy(Qt::NoFocus);        
        QPixmap pauseIcon(":/backPicture/pause.png");
        pauseB->setIcon(pauseIcon);
        pauseB->setIconSize(size);
        pauseB->setGeometry(QRect(330, 450, 98, 45));

        exitB = new QPushButton(All_Area);
        exitB->setObjectName(QStringLiteral("exitB"));
        exitB->setFocusPolicy(Qt::NoFocus);
        QPixmap exitIcon(":/backPicture/exit.png");
        exitB->setIcon(exitIcon);
        exitB->setIconSize(size);
        exitB->setGeometry(QRect(330, 510, 98, 45));

        game_area = new game_area_frame(All_Area);
        game_area->setObjectName(QStringLiteral("game_area"));
        game_area->setFrameStyle(QFrame::Panel | QFrame::Raised);
        game_area->setFocusPolicy(Qt::StrongFocus);     //设置焦点，用于键盘事件获取
        game_area->setGeometry(QRect(10, 20, 300, 600));
        //设置标签字体颜色为白色
        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::white);
        next_label = new QLabel(All_Area);
        next_label->setObjectName(QStringLiteral("next_label"));
        next_label->setPalette(pe);
        next_label->setGeometry(QRect(318, 20, 41, 31));

        level_label = new QLabel(All_Area);
        level_label->setObjectName(QStringLiteral("level_label"));
        level_label->setPalette(pe);
        level_label->setGeometry(QRect(318, 185, 54, 12));

        score_label = new QLabel(All_Area);
        score_label->setObjectName(QStringLiteral("score_label"));
        score_label->setPalette(pe);
        score_label->setGeometry(QRect(318, 250, 54, 12));

        score = new QLCDNumber(All_Area);
        score->setObjectName(QStringLiteral("score"));
        score->setGeometry(QRect(318, 270, 125, 100));

        retranslateUi(All_Area);

        QMetaObject::connectSlotsByName(All_Area);
    } // setupUi

    void retranslateUi(QWidget *All_Area)
    {
        All_Area->setWindowTitle(QApplication::translate("All_Area", "Form", 0));
        startB->setText(QApplication::translate("All_Area", "Start", 0));
        pauseB->setText(QApplication::translate("All_Area", "Pause", 0));
        exitB->setText(QApplication::translate("All_Area", "Exit ", 0));
        next_label->setText(QApplication::translate("All_Area", "Next", 0));
        level_label->setText(QApplication::translate("All_Area", "Level", 0));
        score_label->setText(QApplication::translate("All_Area", "Score", 0));
    } // retranslateUi
};

namespace Ui {
class All_Area: public Ui_All_Area {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGN_H
