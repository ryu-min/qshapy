#include "arrowitem.h"

#include <QPainter>


shapy::ArrowItem::ArrowItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_direction(0)
    , m_arrowSize(40)
{
    setPen(QPen(Qt::black, 3));
    setBrush(Qt::red);
}

QRectF shapy::ArrowItem::boundingRect() const
{
    return QRectF(-m_arrowSize/2, -m_arrowSize/2,
                  m_arrowSize*2, m_arrowSize*2);
}

void shapy::ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(pen());
    painter->save();
    painter->rotate(m_direction);
    painter->drawLine(0, 0, m_arrowSize, 0);
    painter->drawLine(m_arrowSize, 0, m_arrowSize - 5, -5);
    painter->drawLine(m_arrowSize, 0, m_arrowSize - 5, 5);
    painter->restore();
}
