#include "scene.h"

#include <QKeyEvent>

shapy::Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
    , m_boundary(new QGraphicsRectItem(QRectF(0, 0, 400, 400)))
    , m_movableItem(new QGraphicsRectItem(QRectF(0, 0, 50, 50)))
    , m_moveTimer()
    , m_velocity(QPointF(1, 1.4))
    , m_effect()
    , m_animation(nullptr)
{
    m_boundary->setPen(QPen(Qt::transparent, 0));
    addItem(m_boundary);

    m_movableItem->setBrush(QBrush(Qt::red));
    m_movableItem->setPen(QPen(Qt::black, 1));
    addItem(m_movableItem);
    m_movableItem->setPos(110, 20);

    QObject::connect(&m_moveTimer, &QTimer::timeout, this, &shapy::Scene::moveItems);



    QObject::connect(&m_traceTimer, &QTimer::timeout, this, &shapy::Scene::drawTrace);
}

void shapy::Scene::setBoundarySize(const QSize & size)
{
    m_boundary->setRect(0, 0, size.width(), size.height());
}

QPointF shapy::Scene::getCenter()
{
    QRectF boundaryRect = m_boundary->rect();
    return m_boundary->mapToScene(boundaryRect.center());
}

void shapy::Scene::moveItems()
{
    QRectF boundaryRect = m_boundary->boundingRect();
    QRectF itemRect = m_movableItem->boundingRect().translated(m_movableItem->pos() + m_velocity);
    if (!boundaryRect.contains(itemRect)) {
        QPointF newPos = m_movableItem->pos() + m_velocity;
        if ( newPos.x() <= boundaryRect.left() ||
             newPos.x() + itemRect.width() >= boundaryRect.right() ) {
            m_velocity.setX(-m_velocity.x());
        }
        if ( newPos.y() <= boundaryRect.top() ||
             newPos.y() + itemRect.height() >= boundaryRect.bottom() ) {
            m_velocity.setY(-m_velocity.y());
        }
    }
    m_movableItem->setPos( m_movableItem->pos() + m_velocity);
}

void shapy::Scene::drawTrace()
{
    addRect(m_movableItem->boundingRect().translated(m_movableItem->pos()),
            m_movableItem->pen(), QBrush(m_effect.color()));
}

void shapy::Scene::stopMoving()
{
    m_moveTimer.stop();
    m_traceTimer.stop();
    m_animation->pause();
}

void shapy::Scene::resumeMoving()
{
    /// for now this part is weard but it should leave inside item i guess
    if ( !m_animation ) {
        m_movableItem->setGraphicsEffect(&m_effect);
        m_animation = new QPropertyAnimation(&m_effect, "color", this);
        m_animation->setDuration(100000);
        m_animation->setStartValue(QBrush(Qt::red));
        m_animation->setKeyValueAt(0.5, QBrush(Qt::green));
        m_animation->setEndValue(QBrush(Qt::blue));
        m_animation->start();

    } else {
        m_animation->resume();
    }

    m_moveTimer.start(10);
    m_traceTimer.start(50);
}

void shapy::Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (m_moveTimer.isActive()) {
            stopMoving();
        } else {
            resumeMoving();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}
