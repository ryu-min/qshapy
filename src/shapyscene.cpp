#include "shapyscene.h"

#include <QGraphicsRectItem>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsColorizeEffect>

shapy::Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    QGraphicsRectItem * boundary = new QGraphicsRectItem(QRectF(0, 0, 400, 600));
    boundary->setPen(QPen(Qt::black, 2));
    addItem(boundary);

    QGraphicsRectItem * movableItem = new QGraphicsRectItem(QRectF(0, 0, 50, 50));
    movableItem->setBrush(QBrush(Qt::blue));
    movableItem->setPen(QPen(Qt::black, 1));
    addItem(movableItem);
    movableItem->setPos(110, 20);

    QTimer * moveTimer = new QTimer;
    QPointF * velocity = new QPointF(1, 1.4);
    QObject::connect(moveTimer, &QTimer::timeout, [=](){
        QRectF boundaryRect = boundary->boundingRect();
        QRectF itemRect = movableItem->boundingRect().translated(movableItem->pos() + *velocity);
        if (!boundaryRect.contains(itemRect)) {
            QPointF newPos = movableItem->pos() + *velocity;
            if ( newPos.x() <= boundaryRect.left() ||
                 newPos.x() + itemRect.width() >= boundaryRect.right() ) {
                velocity->setX(-velocity->x());
            }
            if ( newPos.y() <= boundaryRect.top() ||
                 newPos.y() + itemRect.height() >= boundaryRect.bottom() ) {
                velocity->setY(-velocity->y());
            }
        }
        movableItem->setPos( movableItem->pos() + *velocity);
    });
    moveTimer->start(10);

    QGraphicsColorizeEffect * effect = new QGraphicsColorizeEffect;
    movableItem->setGraphicsEffect(effect);

    QPropertyAnimation * animation = new QPropertyAnimation(effect, "color");
    animation->setDuration(100000);
    animation->setStartValue(QBrush(Qt::red));
    animation->setKeyValueAt(0.5, QBrush(Qt::green));
    animation->setEndValue(QBrush(Qt::blue));
    animation->start();

    QTimer * traceTimer = new QTimer;
    QObject::connect(traceTimer, &QTimer::timeout, [=](){
        addRect(movableItem->boundingRect().translated(movableItem->pos()),
                      movableItem->pen(), QBrush(effect->color()));
    });
    traceTimer->start(50);



}
