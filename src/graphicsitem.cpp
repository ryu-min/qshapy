#include "graphicsitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>

#include <limits>

shapy::GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_velocity(QPointF(1.0, 1.0))
    , m_colorEffect()
    , m_colorAnimation()
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setZValue( std::numeric_limits<qreal>::max() );

    m_colorAnimation.setTargetObject(&m_colorEffect);
    m_colorAnimation.setPropertyName("color");
    m_colorAnimation.setDuration(100000);
    m_colorAnimation.setStartValue(QBrush(Qt::red));
    m_colorAnimation.setKeyValueAt(0.5, QBrush(Qt::green));
    m_colorAnimation.setEndValue(QBrush(Qt::blue));

    setBrush(Qt::red);
}

QPointF shapy::GraphicsItem::velocity() const noexcept
{
    return m_velocity;
}

void shapy::GraphicsItem::setVelocity(const QPointF &v) noexcept
{
    m_velocity = v;
}

QPointF shapy::GraphicsItem::nextPos() const noexcept
{
    return pos() + m_velocity;
}

bool shapy::GraphicsItem::collidesWithItem(GraphicsItem *other) const noexcept
{
    QRectF thisRect = boundingRect().translated(pos());
    QRectF otherRect = other->boundingRect().translated(other->pos());
    return thisRect.intersects(otherRect);
}

void shapy::GraphicsItem::move()
{
    setPos( nextPos() );
}

void shapy::GraphicsItem::startMoving()
{
    if (m_colorAnimation.state() == QAbstractAnimation::Paused) {
        m_colorAnimation.resume();
    } else {
        m_colorAnimation.start();
    }
}

void shapy::GraphicsItem::stopMoving()
{
    m_colorAnimation.pause();
}

