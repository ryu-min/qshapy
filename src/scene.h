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
        void startMoving();

    protected:
        void keyPressEvent(QKeyEvent *event);

    protected:
        QGraphicsRectItem * m_boundary;
        QTimer m_moveTimer;
        QTimer m_traceTimer;
        QList<GraphicsItem*> m_items;
    };
}


