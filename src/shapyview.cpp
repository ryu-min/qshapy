#include "shapyview.h"
#include <QResizeEvent>

#include "shapyscene.h"

shapy::View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);
}

void shapy::View::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    QGraphicsScene * graphicsScene = scene();
    if (graphicsScene) {
        Scene * shapyScene = dynamic_cast<Scene*>(graphicsScene);
        Q_ASSERT(shapyScene);
        shapyScene->setBoundarySize( event->size() - QSize(30, 30));
        centerOn( mapFromScene(shapyScene->getCenter() ));
    }

}
