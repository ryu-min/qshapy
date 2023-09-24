#pragma once

#include <QGraphicsItem>

namespace shapy
{
    class GraphicsItem : public QAbstractGraphicsShapeItem
    {
    public:
        GraphicsItem(QGraphicsItem *parent = nullptr);
    };
}


