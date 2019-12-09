#include "temperaturereader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TemperatureReader w;
    w.show();
    return a.exec();
}
