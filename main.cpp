#include "quickpass.h"
#include <QApplication>

int main( int argc, char *argv[] ){
    QApplication application(argc, argv);
    Quickpass quickpass;

    quickpass.SetEditMode(false);
    quickpass.LoadCurrentAccounts();
    quickpass.show();
    
    return application.exec();
}
