#include "window.h"

#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    try {
        w.show();
    } catch (exception e) {
        qDebug() << e.what() << endl;
    }
    return a.exec();
}
