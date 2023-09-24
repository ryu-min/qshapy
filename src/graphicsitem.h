#pragma once

#include <QGraphicsItem>
#include <QObject>

namespace shapy
{
    class Scene;
    class GraphicsItem : public QObject, public QAbstractGraphicsShapeItem
    {
        Q_OBJECT
    public:
        GraphicsItem(QGraphicsItem *parent = nullptr);

        QPointF velocity() const noexcept;
        void setVelocity(const QPointF & v) noexcept;

        QPointF nextPos();
        QPointF prevPos();

    public slots:
        void move();
        virtual void drawTrace(Scene * scene) = 0;

    protected:
        QPointF m_velocity;
    };
}


