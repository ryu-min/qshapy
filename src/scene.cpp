#include "scene.h"

#include <QKeyEvent>

shapy::Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
    , m_boundary(new QGraphicsRectItem(QRectF(0, 0, 400, 400)))
    , m_movableItem(new QGraphicsRectItem(QRectF(0, 0, 50, 50)))
    , m_moveTimer()
    , m_velocity(QPointF(1, 1.4))
    , m_effect()
    , m_animation(nullptr)
{
    GraphicsRectItem * rectItem1  = new GraphicsRectItem;
    rectItem1->setBrush(QBrush(Qt::blue));
    m_items.push_back(rectItem1);
    addItem(rectItem1);


    GraphicsRectItem * rectItem2  = new GraphicsRectItem;
    rectItem2->setBrush(QBrush(Qt::red));
    rectItem2->setVelocity(QPointF(0.5, -0.7));
    m_items.push_back(rectItem2);
    addItem(rectItem2);


    rectItem1->setPos(50, 50);
    rectItem2->setPos(0, 100);


    m_boundary->setPen(QPen(Qt::transparent, 0));
    addItem(m_boundary);

    m_movableItem->setBrush(QBrush(Qt::red));
    m_movableItem->setPen(QPen(Qt::black, 1));
    addItem(m_movableItem);
    m_movableItem->setPos(110, 20);

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
    addRect(m_movableItem->boundingRect().translated(m_movableItem->pos()),
            m_movableItem->pen(), QBrush(m_effect.color()));
}

void shapy::Scene::stopMoving()
{
    m_moveTimer.stop();
    m_traceTimer.stop();
    m_animation->pause();
}

void shapy::Scene::resumeMoving()
{
    /// for now this part is weard but it should leave inside item i guess
    if ( !m_animation ) {
        m_movableItem->setGraphicsEffect(&m_effect);
        m_animation = new QPropertyAnimation(&m_effect, "color", this);
        m_animation->setDuration(100000);
        m_animation->setStartValue(QBrush(Qt::red));
        m_animation->setKeyValueAt(0.5, QBrush(Qt::green));
        m_animation->setEndValue(QBrush(Qt::blue));
        m_animation->start();

    } else {
        m_animation->resume();
    }

    m_moveTimer.start(10);
    m_traceTimer.start(50);
}

void shapy::Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (m_moveTimer.isActive()) {
            stopMoving();
        } else {
            resumeMoving();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}
