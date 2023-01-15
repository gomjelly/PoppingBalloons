#include "PoppingBalloons.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PoppingBalloons w;
    w.show();
    return a.exec();
}
