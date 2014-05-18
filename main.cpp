#include <QApplication>
//#include <QWindowsStyle>
//#include <QWindowsXPStyle>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
//    app.setStyle(new QWindowsStyle);
    app.setWindowIcon(QIcon(":/EnergyIcon.png"));

    MainWindow w;
    w.show();    

    return app.exec();
}
