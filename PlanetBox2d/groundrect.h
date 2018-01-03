#ifndef GROUNDRECT_H
#define GROUNDRECT_H

#include <QGraphicsRectItem>
#include <Box2D/Box2D.h>

#include <functions.h>

class GroundRect : public QGraphicsRectItem
{
public:
    GroundRect(b2World *world, QSizeF size, QPointF initPos, qreal angle);
    ~GroundRect();

private:
    b2Body* body; //Тело для физики
};

#endif // GROUNDRECT_H
