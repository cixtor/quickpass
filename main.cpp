#include "quickpass.h"
#include <QApplication>

int main( int argc, char *argv[] ){
    QApplication application(argc, argv);
    Quickpass window;
    window.show();
    
    return application.exec();
}
