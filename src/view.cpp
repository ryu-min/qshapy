#include "view.h"
#include "scene.h"
#include "graphicsrectitem.h"

#include <QResizeEvent>
#include <QMenu>

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

void shapy::View::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *addAction = menu.addAction("Add Rectangle");
    QAction *selectedAction = menu.exec(event->globalPos());
    if (selectedAction == addAction) {
        Scene * shapyScene = dynamic_cast<Scene*>(scene());
        Q_ASSERT(shapyScene);
        GraphicsRectItem * rectItem = new GraphicsRectItem;
        rectItem->setPos(mapToScene(event->pos()));
        shapyScene->addShapyItem(rectItem);
    }
}
