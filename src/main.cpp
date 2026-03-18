#include <QApplication>
#include <QQuickStyle>
#include "src/gui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");  // или Material, Universal и т.д.

    MainWindow window;
    window.resize(1280, 800);
    window.show();

    return app.exec();
}