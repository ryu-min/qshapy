#pragma once

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QGraphicsColorizeEffect>


namespace shapy
{
    class Scene : public QGraphicsScene
    {
    public:
        Scene(QObject * parent = nullptr);

        void setBoundarySize(const QSize size);
        QPointF getCenter();

    protected:
        void moveItems();
        void drawTrace();

    protected:
        QGraphicsRectItem * m_boundary;
        QGraphicsRectItem * m_movableItem;
        QTimer m_moveTimer;
        QPointF m_velocity;
        QGraphicsColorizeEffect m_effect;
        QTimer m_traceTimer;
    };
}


