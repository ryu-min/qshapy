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

    private:
        qreal m_direction;
        qreal m_arrowSize;
    };
}
