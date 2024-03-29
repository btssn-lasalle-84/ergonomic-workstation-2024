#include "ihm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHM ihm;
    ihm.show();
    return a.exec();
}
