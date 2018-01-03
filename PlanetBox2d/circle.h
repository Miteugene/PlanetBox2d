#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsEllipseItem>
#include <Box2D/Box2D.h>

#include <functions.h>
#include <mutex>


class Circle : public QGraphicsEllipseItem
{
public:
    Circle(b2World *world, qreal radius, QPointF pos);
    ~Circle();

public:
    b2Body* body;

public:
    virtual void advance(int phase);
    void deleteCircle();
    QPointF getPos();

private:
std::mutex stateMutex;

protected:
    // События мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // CIRCLE_H
