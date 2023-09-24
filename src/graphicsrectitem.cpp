#include "graphicsrectitem.h"
#include "scene.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

shapy::GraphicsRectItem::GraphicsRectItem(QGraphicsItem *parent)
    : GraphicsItem(parent)
{
//    setPen(QPen(Qt::transparent, 0));
}

QRectF shapy::GraphicsRectItem::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void shapy::GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush( brush() );
    painter->setPen( pen() );
    painter->drawRect(0, 0, 50, 50);
}

void shapy::GraphicsRectItem::drawTrace(Scene *scene)
{
    scene->addRect(boundingRect().translated(prevPos()), QPen(Qt::black, 1), brush());
}
