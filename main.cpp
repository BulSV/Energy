#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/EnergyIcon.png"));

    MainWindow w;
    w.show();    

    return app.exec();
}
