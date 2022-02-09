#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;

    Qt::WindowFlags flags = nullptr;
    flags |= Qt::WindowMinimizeButtonHint;
//    w.setWindowFlags(flags);
    w.show();

    return app.exec();
}
