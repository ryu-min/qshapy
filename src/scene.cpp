#include "scene.h"

#include <QKeyEvent>

shapy::Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
    , m_boundary(new QGraphicsRectItem(QRectF(0, 0, 400, 400)))
    , m_moveTimer()
    , m_traceTimer()
    , m_items()
{
    GraphicsRectItem * rectItem1  = new GraphicsRectItem;
    m_items.push_back(rectItem1);
    addItem(rectItem1);
    rectItem1->setPos(300, 50);


    GraphicsRectItem * rectItem2  = new GraphicsRectItem;
    rectItem2->setVelocity(QPointF(-1.0, 1.0));
    m_items.push_back(rectItem2);
    addItem(rectItem2);
    rectItem2->setPos(0, 100);

    m_boundary->setPen(QPen(Qt::transparent, 0));
    addItem(m_boundary);

    QObject::connect(&m_moveTimer, &QTimer::timeout, this, &shapy::Scene::moveItems);
    QObject::connect(&m_traceTimer, &QTimer::timeout, this, &shapy::Scene::drawTrace);
}

void shapy::Scene::setBoundarySize(const QSize & size)
{
    m_boundary->setRect(0, 0, size.width(), size.height());
}

QPointF shapy::Scene::getCenter()
{
    QRectF boundaryRect = m_boundary->rect();
    return m_boundary->mapToScene(boundaryRect.center());
}

void shapy::Scene::moveItems()
{
    QRectF boundaryRect = m_boundary->boundingRect();
    for (GraphicsItem * item : m_items) {
        moveItem(item, boundaryRect);
    }
}

void shapy::Scene::moveItem(GraphicsItem *item, const QRectF &boundary)
{
    QPointF newItemPos = item->nextPos();
    QRectF itemRect = item->boundingRect().translated(newItemPos);
    if (!boundary.contains(itemRect)) {
        QPointF newVelocity = item->velocity();
        if ( newItemPos.x() <= boundary.left() ||
             newItemPos.x() + itemRect.width() >= boundary.right() ) {
            newVelocity.setX(-newVelocity.x());
        }
        if ( newItemPos.y() <= boundary.top() ||
             newItemPos.y() + itemRect.height() >= boundary.bottom() ) {
            newVelocity.setY(-newVelocity.y());
        }
        item->setVelocity(newVelocity);
    }
    item->move();
}

void shapy::Scene::drawTrace()
{
    for (GraphicsItem * item : m_items) {
        item->drawTrace();
    }
}

void shapy::Scene::stopMoving()
{
    m_moveTimer.stop();
    m_traceTimer.stop();
    for ( GraphicsItem * item : m_items ) {
        item->stopMoving();
    }
}

void shapy::Scene::startMoving()
{
    m_moveTimer.start(10);
    m_traceTimer.start(50);
    for ( GraphicsItem * item : m_items ) {
        item->startMoving();
    }
}

void shapy::Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (m_moveTimer.isActive()) {
            stopMoving();
        } else {
            startMoving();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}
