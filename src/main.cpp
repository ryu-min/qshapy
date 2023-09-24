#include <QApplication>

#include "view.h"
#include "scene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    shapy::Scene scene;
    shapy::View view;
    view.setScene(&scene);
    view.show();
    view.resize(400, 400);

    return a.exec();
}
