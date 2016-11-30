#include "quickpass.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Quickpass w;

  w.SetEditMode(false);
  w.LoadCurrentAccounts();
  w.show();

  return a.exec();
}
