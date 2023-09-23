#pragma once

#include <QGraphicsItem>

namespace shapy
{
    class GraphicsItem : public QGraphicsItem
    {
    public:
        GraphicsItem(QGraphicsItem *parent = nullptr);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    protected:
        QPointF m_startMovingPos;
    };
}


