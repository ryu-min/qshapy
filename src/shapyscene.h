#pragma once

#include <QGraphicsScene>

namespace shapy
{
    class Scene : public QGraphicsScene
    {
    public:
        Scene(QObject * parent = nullptr);
    };
}


