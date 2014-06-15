#include <QApplication>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/EnergyIcon.png"));

    MainWindow w;
    w.show();

    return app.exec();
}
