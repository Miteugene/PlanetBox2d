#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>

#include <scene.h>
#include <circle.h>
#include <groundrect.h>

#include <functions.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    QGraphicsView* graphicsView;

private slots:
    void pushButtonClick();
    void clearButtonClick();

private:
    Ui::Widget *ui;
    Scene* scene;
    QTimer* frameTimer;
    b2World* world;

};

#endif // WIDGET_H
