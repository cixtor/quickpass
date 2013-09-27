#include "quickpass.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Quickpass w;
    w.show();
    
    return a.exec();
}
