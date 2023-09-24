#include "view.h"
#include <QResizeEvent>

#include "scene.h"

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
        shapyScene->setBoundarySize( event->size() );
    }

}
