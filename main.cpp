#include <QApplication>
#include "src/MainWindow.hpp"
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    
    MainWindow window;

    return app.exec();
}
