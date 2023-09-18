#include <QApplication>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>

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
    movableItem->setBrush(QBrush(Qt::red));
    scene.addItem(movableItem);
    movableItem->setPos(60, 20);

    QTimer t;
    QRectF boundaryRect = boundary->boundingRect();
    QPointF velocity = QPointF(1, 2);
    QObject::connect(&t, &QTimer::timeout, [movableItem, &boundaryRect, &velocity](){
        QRectF itemRect = movableItem->boundingRect().translated(movableItem->pos());
        if (!boundaryRect.contains(itemRect)) {
            if ( movableItem->x() <= boundaryRect.left() ||
                 movableItem->x() + itemRect.width() >= boundaryRect.right() ) {
                velocity.setX(-velocity.x());
            }
            if ( movableItem->y() <= boundaryRect.top() ||
                 movableItem->y() + itemRect.height() >= boundaryRect.bottom() ) {
                velocity.setY(-velocity.y());
            }

        }
        movableItem->setPos( movableItem->pos() + velocity);
    });
    t.start(10);

    view.resize(600, 600);
    view.show();
    return a.exec();
}
