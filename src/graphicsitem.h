#pragma once

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>

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

    public slots:
        void move();
        virtual void drawTrace() = 0;
        virtual void startMoving();
        virtual void stopMoving();

    protected:
        QPointF m_velocity;
        QGraphicsColorizeEffect m_colorEffect;
        QPropertyAnimation m_colorAnimation;
    };
}


