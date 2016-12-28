#include "xmlapp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xmlApp w;
    w.show();

    return a.exec();
}
