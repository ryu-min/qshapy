#include "graphicsitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QAction>
#include <QMenu>

#include <limits>

shapy::GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
    , m_velocity(QPointF(1.0, 1.0))
    , m_colorEffect()
    , m_colorAnimation()
    , m_arrowItem(new ArrowItem(this))
{
    m_arrowItem->setParentItem(this);
    m_arrowItem->hide();
    setFlag(QGraphicsItem::ItemIsMovable);
//    setFlag(QGraphicsItem::ItemClipsChildrenToShape);

    setZValue( std::numeric_limits<qreal>::max() );

    m_colorAnimation.setTargetObject(&m_colorEffect);
    m_colorAnimation.setPropertyName("color");
    m_colorAnimation.setDuration(100000);
    m_colorAnimation.setStartValue(QBrush(Qt::red));
    m_colorAnimation.setKeyValueAt(0.5, QBrush(Qt::green));
    m_colorAnimation.setEndValue(QBrush(Qt::blue));

    setBrush(Qt::red);
}

QRectF shapy::GraphicsItem::boundingRect() const
{
    if (m_arrowItem->isVisible()) {
        return m_arrowItem->boundingRect();
    }
    return QRectF();
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

void shapy::GraphicsItem::contextMenu(const QPoint & pos)
{
    QMenu menu;
    QAction * changeDirection = menu.addAction("Change direction");
    changeDirection->setCheckable(true);
    changeDirection->setChecked(m_arrowItem->isVisible());
    QAction *selectedAction = menu.exec(pos);
    if (selectedAction == changeDirection) {
        m_arrowItem->setVisible( changeDirection->isChecked());
    }
}

void shapy::GraphicsItem::move()
{
    setPos( nextPos() );
}

void shapy::GraphicsItem::startMoving()
{
    m_arrowItem->hide();
    setVelocity(m_arrowItem->velocity());
    if (m_colorAnimation.state() == QAbstractAnimation::Paused) {
        m_colorAnimation.resume();
    } else {
        m_colorAnimation.start();
    }
}

void shapy::GraphicsItem::stopMoving()
{
    m_arrowItem->setVelocity( velocity() );
    m_arrowItem->show();
    m_colorAnimation.pause();
}

void shapy::GraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

}

