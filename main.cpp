#include "timedslider.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    timedslider w;
    w.show();
    return a.exec();
}
