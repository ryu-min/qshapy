#pragma once

#include "graphicsitem.h"

namespace shapy
{
    class GraphicsRectItem : public GraphicsItem
    {
    public:
        GraphicsRectItem(QGraphicsItem * parent = nullptr);
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    };
}


