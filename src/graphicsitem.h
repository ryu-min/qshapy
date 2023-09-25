#pragma once

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>

#include "arrowitem.h"

namespace shapy
{
    class Scene;
    class GraphicsItem : public QObject, public QAbstractGraphicsShapeItem
    {
        Q_OBJECT
    public:
        GraphicsItem(QGraphicsItem *parent = nullptr);

        QRectF boundingRect() const override;

        QPointF velocity() const noexcept;
        void setVelocity(const QPointF & v) noexcept;
        QPointF nextPos() const noexcept;
        bool collidesWithItem(GraphicsItem *other) const noexcept;

        void contextMenu(const QPoint &pos);

    public slots:
        void move();
        virtual void drawTrace() = 0;
        virtual void startMoving();
        virtual void stopMoving();

    protected:
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    protected:
        QPointF m_velocity;
        QGraphicsColorizeEffect m_colorEffect;
        QPropertyAnimation m_colorAnimation;
        ArrowItem * m_arrowItem;



    };
}


