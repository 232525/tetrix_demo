#ifndef UI_FROM_DESIGN_H
#define UI_FROM_DESIGN_H

#include "design.h"
#include "game_area_frame.h"
#include <QFrame>
#include <QWidget>
#include <QBasicTimer>
#include <QPointer>
#include <QPainter>

class ui_from_design : public QWidget, public Ui_All_Area
{
    Q_OBJECT
public:
    ui_from_design();
signals:
};

#endif // UI_FROM_DESIGN_H
