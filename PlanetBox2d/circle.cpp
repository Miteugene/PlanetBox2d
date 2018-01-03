#include <circle.h>
#include <QGraphicsView>

#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>


Circle::Circle(b2World *world, qreal radius, QPointF pos):
    QGraphicsEllipseItem(0)
{
    setPen(QPen(Qt::black));

    setRect(-fromB2(radius), -fromB2(radius), fromB2(radius*2), fromB2(radius*2));
    setBrush(QBrush(QColor(random(50, 255), random(50, 255), random(50, 255))));


    QGraphicsEllipseItem::setPos(fromB2(pos.x()), fromB2(pos.y()));

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    bodyDef.position.Set(pos.x(), pos.y());
    bodyDef.linearDamping = 0.00f;

    body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2Fixture* fixture = body->CreateFixture(&shape, 20.0f); // Второй параметр задает плотность
    fixture->SetRestitution(0.1f); // упругость
    fixture->SetFriction(0.0f); // трение

    body->SetSleepingAllowed(false);

}

Circle::~Circle()
{
    body->GetWorld()->DestroyBody(body);
}


void Circle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void Circle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->body->SetLinearVelocity( b2Vec2(toB2(event->pos().x()), toB2(event->pos().y())) );
}

void Circle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}

void Circle::deleteCircle()
{
    delete this;
}

QPointF Circle::getPos()
{
    std::lock_guard<std::mutex> lock(stateMutex);
    return this->pos();
}

void Circle::advance(int phase)
{
    if (phase)
        QGraphicsEllipseItem::setPos(fromB2(body->GetPosition().x), fromB2(body->GetPosition().y));
}
