#include <scene.h>
#include <circle.h>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>


Scene::Scene(qreal x, qreal y, qreal width, qreal height, b2World *world)
    :QGraphicsScene(fromB2(x), fromB2(y), fromB2(width), fromB2(height))
    , physics(true)
    , t(&Scene::physicsThread, this)
{
    this->world = world;
}

Scene::~Scene()
{
    physics = false;
    t.join();
    clearAll();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    Circle *circle = qgraphicsitem_cast<Circle *>(item);

    if (event->button() == Qt::RightButton) {
        if(circle) {
            deleteCircle(circle);
        } else {
            addCircle(event->scenePos());
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }

}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::clearAll()
{
    clear();
    circleList.clear();
}

void Scene::deleteCircle(Circle *circle)
{
    circleList.removeOne(circle);
    removeItem(circle);
    delete circle;
}

void Scene::addCircle(QPointF pos)
{
    Circle* new_cir = new Circle(world, toB2(RADIUS), QPointF(toB2(pos.x()), toB2(pos.y())) );
    circleList << new_cir;
    addItem(new_cir);
}

void Scene::addCircle()
{
    QPointF pos(random(0, this->width()), random(0, this->height()));
    Circle* new_cir = new Circle(world, toB2(RADIUS), QPointF(toB2(pos.x()), toB2(pos.y())));
    circleList << new_cir;
    addItem(new_cir);
}


void Scene::advance()
{
    world->Step(1.0f/60.0f, 6, 2);

    QGraphicsScene::advance();
}

QPointF Scene::getPowerToObject(Circle* circle1, Circle* circle2)
{
    QPointF pos1 = circle1->getPos();
    QPointF pos2 = circle2->getPos();

    qreal r = toB2(distance(pos1, pos2) - 2 * RADIUS);
    qreal f = (1/r - 1/pow(r, 2) );

    QPointF pos = pos2 - pos1;
    qreal alpha = atan2(pos.ry(), pos.rx());

    return QPointF(f * cos(alpha), f * sin(alpha));
}

void Scene::getPower()
{
    std::lock_guard<std::mutex> lock(circleMutex);

    static auto updateTime = std::chrono::system_clock::now();

    QList<QPointF> getVectors;

    foreach (Circle* cir1, circleList) {

        QPointF pos1 = cir1->getPos();
        QPointF result_vec(0, 0);

        foreach (Circle* cir2, circleList) {
            if(cir1 == cir2)
                continue;

            QPointF vec = getPowerToObject(cir1, cir2);
            result_vec += vec;
        }

        auto currentTime = std::chrono::system_clock::now();
        double t = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - updateTime).count();

        getVectors << result_vec;
    }

    for(int i = 0; i < circleList.size(); ++i) {
        circleList.at(i)->body->ApplyForce(b2Vec2(getVectors.at(i).x(), getVectors.at(i).y()), circleList.at(i)->body->GetWorldCenter(), true);
    }

    updateTime = std::chrono::system_clock::now();
}


void Scene::physicsThread()
{
    while(physics) {
        const auto start = std::chrono::system_clock::now();
        getPower();
        const auto end = std::chrono::system_clock::now();
        int difference = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        int sleep = MICRO / FPS - difference;
        if (sleep > 0)
            std::this_thread::sleep_for(std::chrono::microseconds(sleep));
    }
}
