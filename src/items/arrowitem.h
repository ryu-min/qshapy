#pragma once

#include <QGraphicsItem>

namespace shapy
{
    class ArrowItem : public QAbstractGraphicsShapeItem
    {
    public:
        ArrowItem(QGraphicsItem * parent = nullptr);
        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        QPointF velocity() const;
        void setVelocity(const QPointF & v);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    protected:
        qreal m_direction;
        qreal m_arrowSize;
        QPointF m_lastPos;

    };
}
