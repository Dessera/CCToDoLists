#include <QApplication>
#include "CCToDoMainWindow.h"

int main(int argc, char *argv[]) {
    QApplication     a(argc, argv);
    CCToDoMainWindow w;
    w.show();
    return a.exec();
}
