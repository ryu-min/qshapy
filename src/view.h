#pragma once

#include <QGraphicsView>

namespace shapy
{
    class View : public QGraphicsView
    {
    public:
        View(QWidget * parent = nullptr);

    protected:
        void resizeEvent(QResizeEvent *event) override;
    };
}


