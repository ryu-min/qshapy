#include "shapyscene.h"

#include <QPropertyAnimation>

shapy::Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
    , m_boundary(new QGraphicsRectItem(QRectF(0, 0, 400, 400)))
    , m_movableItem(new QGraphicsRectItem(QRectF(0, 0, 50, 50)))
    , m_moveTimer()
    , m_velocity(QPointF(1, 1.4))
    , m_effect()
{
    m_boundary->setPen(QPen(Qt::black, 2));
    addItem(m_boundary);

    m_movableItem->setBrush(QBrush(Qt::blue));
    m_movableItem->setPen(QPen(Qt::black, 1));
    addItem(m_movableItem);
    m_movableItem->setPos(110, 20);

    QObject::connect(&m_moveTimer, &QTimer::timeout, this, &shapy::Scene::moveItems);
    m_moveTimer.start(10);

    m_movableItem->setGraphicsEffect(&m_effect);

    QPropertyAnimation * animation = new QPropertyAnimation(&m_effect, "color", this);
    animation->setDuration(100000);
    animation->setStartValue(QBrush(Qt::red));
    animation->setKeyValueAt(0.5, QBrush(Qt::green));
    animation->setEndValue(QBrush(Qt::blue));
    animation->start();

    QObject::connect(&m_traceTimer, &QTimer::timeout, this, &shapy::Scene::drawTrace);
    m_traceTimer.start(50);
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
    QRectF itemRect = m_movableItem->boundingRect().translated(m_movableItem->pos() + m_velocity);
    if (!boundaryRect.contains(itemRect)) {
        QPointF newPos = m_movableItem->pos() + m_velocity;
        if ( newPos.x() <= boundaryRect.left() ||
             newPos.x() + itemRect.width() >= boundaryRect.right() ) {
            m_velocity.setX(-m_velocity.x());
        }
        if ( newPos.y() <= boundaryRect.top() ||
             newPos.y() + itemRect.height() >= boundaryRect.bottom() ) {
            m_velocity.setY(-m_velocity.y());
        }
    }
    m_movableItem->setPos( m_movableItem->pos() + m_velocity);
}

void shapy::Scene::drawTrace()
{
    addRect(m_movableItem->boundingRect().translated(m_movableItem->pos()),
                  m_movableItem->pen(), QBrush(m_effect.color()));
}
