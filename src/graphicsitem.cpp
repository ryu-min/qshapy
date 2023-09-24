#include "graphicsitem.h"

#include <QGraphicsSceneMouseEvent>

shapy::GraphicsItem::GraphicsItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
}

