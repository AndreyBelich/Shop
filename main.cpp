#include <QApplication>
#include "mainwindow.h"
#include "clientdatabase.h"

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    MainWindow widget;
    widget.show();
    //ClientDataBase d;
    //d.show();
    return app.exec();
}
