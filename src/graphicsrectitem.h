#pragma once

#include "graphicsitem.h"
#include "scene.h"

namespace shapy
{
    class GraphicsRectItem : public GraphicsItem
    {
    public:
        GraphicsRectItem(QGraphicsItem * parent = nullptr);
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    public slots:
        void drawTrace(Scene * scene) override;
    };
}


