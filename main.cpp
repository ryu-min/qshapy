#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsObject>
#include <QGraphicsColorizeEffect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view;
    view.setScene(&scene);

    QGraphicsRectItem * boundary = new QGraphicsRectItem(QRectF(0, 0, 400, 400));
    boundary->setPen(QPen(Qt::black, 4));
    scene.addItem(boundary);

    QGraphicsRectItem * movableItem = new QGraphicsRectItem(QRectF(0, 0, 50, 50));
    movableItem->setBrush(QBrush(Qt::blue));
    movableItem->setPen(QPen(Qt::black, 1));
    scene.addItem(movableItem);
    movableItem->setPos(30, 20);

    QTimer moveTimer;
    QRectF boundaryRect = boundary->boundingRect();
    QPointF velocity = QPointF(1, 2);
    QObject::connect(&moveTimer, &QTimer::timeout, [movableItem, &boundaryRect, &velocity](){
        QRectF itemRect = movableItem->boundingRect().translated(movableItem->pos() + velocity);
        if (!boundaryRect.contains(itemRect)) {
            QPointF newPos = movableItem->pos() + velocity;
            if ( newPos.x() <= boundaryRect.left() ||
                 newPos.x() + itemRect.width() >= boundaryRect.right() ) {
                velocity.setX(-velocity.x());
            }
            if ( newPos.y() <= boundaryRect.top() ||
                 newPos.y() + itemRect.height() >= boundaryRect.bottom() ) {
                velocity.setY(-velocity.y());
            }
        }
        movableItem->setPos( movableItem->pos() + velocity);
    });
    moveTimer.start(10);

    QGraphicsColorizeEffect effect;
    movableItem->setGraphicsEffect(&effect);

    QPropertyAnimation animation(&effect, "color");
    animation.setDuration(100000);
    animation.setStartValue(QBrush(Qt::red));
    animation.setKeyValueAt(0.5, QBrush(Qt::green));
    animation.setEndValue(QBrush(Qt::blue));
    animation.start();

    QTimer traceTimer;
    QObject::connect(&traceTimer, &QTimer::timeout, [&](){
        scene.addRect(movableItem->boundingRect().translated(movableItem->pos()),
                      movableItem->pen(), QBrush(effect.color()));
    });
    traceTimer.start(50);


    view.resize(600, 600);
    view.show();
    return a.exec();
}
