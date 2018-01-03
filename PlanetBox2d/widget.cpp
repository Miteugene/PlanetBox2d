#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    world = new b2World( b2Vec2(0.0f, GRAVITY) );

    scene = new Scene(0, 0, toB2(formWidth), toB2(formHeight), world);

    this->showMaximized();

    graphicsView = new QGraphicsView();
    graphicsView->setGeometry(0, 0, toB2(formWidth), toB2(formHeight));
    graphicsView->setScene(scene);


    QPushButton* pushButton = new QPushButton("Создать мир", this);
    connect(pushButton, SIGNAL(clicked()), SLOT(pushButtonClick()));

    QPushButton* clearButton = new QPushButton("Удалить все", this);
    connect(clearButton, SIGNAL(clicked()), SLOT(clearButtonClick()));


    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(clearButton);
    mainLayout->addWidget(pushButton);
    mainLayout->addWidget(graphicsView);


    this->setLayout(mainLayout);

    graphicsView->setBackgroundBrush( QColor(40, 40, 40) );
    graphicsView->setRenderHint(QPainter::Antialiasing); // Подключаем сглаживание
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate); //Задаем режим перерисовки


    frameTimer = new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()),
            scene, SLOT(advance()));

    frameTimer->start(1000/FPS);

}

Widget::~Widget()
{
    delete ui;
    delete scene;
    delete world;
}

void Widget::pushButtonClick()
{
    scene->clearAll();

    scene->addItem(new GroundRect(world, QSizeF(toB2(formWidth) + 0.1, 0.1), QPointF(toB2(formWidth) / 2, toB2(formHeight)), 0) );
    scene->addItem(new GroundRect(world, QSizeF(toB2(formWidth) + 0.1, 0.1), QPointF(toB2(formWidth) / 2, 0), 0) );
    scene->addItem(new GroundRect(world, QSizeF(0.1, toB2(formHeight) + 0.1), QPointF(0, toB2(formHeight) / 2), 0) );
    scene->addItem(new GroundRect(world, QSizeF(0.1, toB2(formHeight) + 0.1), QPointF(toB2(formWidth), toB2(formHeight) / 2), 0) );

    for(int i = 0; i < random(minCircles, maxCircles); i++)
        scene->addCircle();
}

void Widget::clearButtonClick()
{
    scene->clearAll();
}
