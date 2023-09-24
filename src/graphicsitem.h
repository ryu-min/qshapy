#pragma once

#include <QGraphicsItem>
#include <QObject>

namespace shapy
{
    class GraphicsItem : public QObject, public QAbstractGraphicsShapeItem
    {
        Q_OBJECT
    public:
        GraphicsItem(QGraphicsItem *parent = nullptr);

        QPointF velocity() const noexcept;
        void setVelocity(const QPointF & v) noexcept;

        QPointF nextPos();

    public slots:
        void move();

    protected:
        QPointF m_velocity;
    };
}


