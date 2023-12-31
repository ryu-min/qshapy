#include "scene.h"

#include <QKeyEvent>

#include <QTimer>
#include <QElapsedTimer>

shapy::Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
    , m_boundary(new QGraphicsRectItem(QRectF(0, 0, 400, 400)))
    , m_moveTimer()
    , m_traceTimer()
    , m_items()
{
    GraphicsRectItem * firstItem = new GraphicsRectItem;
    firstItem->setPos(m_boundary->boundingRect().center() - QPointF(25, 25));
    firstItem->setVelocity(QPointF(-1.0, -1.0));
    addShapyItem(firstItem);

    m_boundary->setPen(QPen(Qt::transparent, 0));
    addItem(m_boundary);

    QObject::connect(&m_moveTimer, &QTimer::timeout, this, &shapy::Scene::moveItems);
    QObject::connect(&m_traceTimer, &QTimer::timeout, this, &shapy::Scene::drawTrace);
}

void shapy::Scene::setBoundarySize(const QSize & size)
{
    m_boundary->setRect(0, 0, size.width(), size.height());
}

void shapy::Scene::addShapyItem(GraphicsItem *item)
{
    addItem(item);
    m_items.push_back(item);
}

void shapy::Scene::moveItems()
{
    QElapsedTimer t; t.start();
    QRectF boundaryRect = m_boundary->boundingRect();
    for (GraphicsItem * item : m_items) {
        moveItem(item, boundaryRect);
    }
    resolveItemCollisions();
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
    m_traceTimer.start(100);
    for ( GraphicsItem * item : m_items ) {
        item->startMoving();
    }
}

void shapy::Scene::resolveItemCollisions()
{
    QElapsedTimer t; t.start();
    for (int i = 0; i < m_items.size(); ++i) {
        for (int j = i + 1; j < m_items.size(); ++j) {
            if (m_items[i]->collidesWithItem(m_items[j])) {
                QPointF v1 = m_items[i]->velocity();
                QPointF v2 = m_items[j]->velocity();
                m_items[i]->setVelocity(v2);
                m_items[j]->setVelocity(v1);
            }
        }
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
