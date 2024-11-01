#include "widget.h"
#include "config.h"

#include <QResource>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QResource::registerResource(RES_PATH);

    Widget w;
    w.show();

    return a.exec();
}
