#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <Box2D/Box2D.h>

#include <functions.h>
#include <circle.h>

#include <thread>
#include <atomic>

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(qreal x, qreal y, qreal width, qreal height, b2World* world);
    ~Scene();

    void addCircle(QPointF pos);
    void addCircle();
    void deleteCircle(Circle *circle);
    void clearAll();

    QPointF getPowerToObject(Circle* circle1, Circle* circle2);
    void getPower();

public:
    std::mutex circleMutex;
    std::thread t;
    std::atomic<bool> physics;
    b2World* world;
    QList<Circle*> circleList;
    void physicsThread();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void advance();
};


#endif // SCENE_H
