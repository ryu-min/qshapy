#include "graphicsitem.h"

#include <QGraphicsSceneMouseEvent>

shapy::GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_velocity(QPointF(1.0, 1.0))
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

QPointF shapy::GraphicsItem::velocity() const noexcept
{
    return m_velocity;
}

void shapy::GraphicsItem::setVelocity(const QPointF &v) noexcept
{
    m_velocity = v;
}

QPointF shapy::GraphicsItem::nextPos()
{
    return pos() + m_velocity;
}

void shapy::GraphicsItem::move()
{
    setPos( nextPos() );
}

