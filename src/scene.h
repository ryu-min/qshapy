#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>

#include "graphicsrectitem.h"

namespace shapy
{
    class Scene : public QGraphicsScene
    {
        Q_OBJECT
    public:
        Scene(QObject * parent = nullptr);

        void setBoundarySize(const QSize &size);
        QPointF getCenter();

    protected slots:
        void moveItems();
        void moveItem(GraphicsItem * item, const QRectF & boundary);
        void drawTrace();
        void stopMoving();
        void resumeMoving();

    protected:
        void keyPressEvent(QKeyEvent *event);

    protected:
        QGraphicsRectItem * m_boundary;
        QGraphicsRectItem * m_movableItem;
        QTimer m_moveTimer;
        QPointF m_velocity;
        QGraphicsColorizeEffect m_effect;
        QTimer m_traceTimer;
        QPropertyAnimation * m_animation;

        QList<GraphicsItem*> m_items;
    };
}


