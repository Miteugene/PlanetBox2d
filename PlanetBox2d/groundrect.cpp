#include <groundrect.h>

#include <QGraphicsView>

GroundRect::GroundRect(b2World *world, QSizeF size, QPointF initPos, qreal angle):
    QGraphicsRectItem(0)
{
    setRect(-fromB2(size.width()/2), -fromB2(size.height()/2),
            fromB2(size.width()), fromB2(size.height()));

    setBrush(QBrush(Qt::white));
    setPen(QPen(Qt::white));

    setPos(fromB2(initPos.x()), fromB2(initPos.y()));
    setRotation(angle);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(initPos.x(), initPos.y());
    bodyDef.angle = 3.14 * angle / 180;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(size.width()/2, size.height()/2);

    body->CreateFixture(&shape, 1.0f);
}

GroundRect::~GroundRect()
{
    body->GetWorld()->DestroyBody(body);
}
