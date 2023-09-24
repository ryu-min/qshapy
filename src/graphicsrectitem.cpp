#include "graphicsrectitem.h"
#include "scene.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

shapy::GraphicsRectItem::GraphicsRectItem(QGraphicsItem *parent)
    : GraphicsItem(parent)
{}

QRectF shapy::GraphicsRectItem::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void shapy::GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if ( m_colorAnimation.state() == QAbstractAnimation::Stopped ) {
        painter->setBrush( brush() );
    } else {
        painter->setBrush( m_colorEffect.color() );
    }
    painter->setPen( pen() );
    painter->drawRect(0, 0, 50, 50);
}

void shapy::GraphicsRectItem::drawTrace()
{
    scene()->addRect(boundingRect().translated(pos()), pen(), m_colorEffect.color());
}
