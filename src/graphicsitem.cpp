#include "graphicsitem.h"

#include <QGraphicsSceneMouseEvent>

shapy::GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{}

void shapy::GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_startMovingPos = event->pos();
    }
    QGraphicsItem::mousePressEvent(event);
}

void shapy::GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPointF delta = event->pos() - m_startMovingPos;
        setPos(pos() + delta);
    }
    QGraphicsItem::mouseMoveEvent(event);
}
