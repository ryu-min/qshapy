#include "arrowitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>


shapy::ArrowItem::ArrowItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_direction(30)
    , m_arrowSize(50)
{
    setFlag(ItemIsSelectable);
    setPen(QPen(Qt::black, 4));
    setBrush(Qt::red);
}

QRectF shapy::ArrowItem::boundingRect() const
{
    return QRectF(-m_arrowSize, -m_arrowSize,
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

QPointF shapy::ArrowItem::velocity() const
{
    qreal rad = m_direction * M_PI / 180;
    qreal x = qCos(rad);
    qreal y = qSin(rad);
    return QPointF(x, y);
}

void shapy::ArrowItem::setVelocity(const QPointF &v)
{
    qreal angle = qAtan2(v.y(), v.x()) * 180 / M_PI;
    m_direction = angle;
    update();
}

void shapy::ArrowItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_lastPos = event->scenePos();
    QAbstractGraphicsShapeItem::mousePressEvent(event);
}

void shapy::ArrowItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF delta = event->scenePos() - m_lastPos;
    qreal angle = atan2(delta.y(), delta.x()) * 180 / M_PI;
    m_direction = angle;
    update();
    QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

void shapy::ArrowItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QAbstractGraphicsShapeItem::mouseReleaseEvent(event);
}
