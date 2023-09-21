#include <QApplication>

#include "shapyview.h"
#include "shapyscene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    shapy::Scene scene;
    shapy::View view;
    view.setScene(&scene);
    view.show();
    view.resize(300, 400);

    return a.exec();
}
