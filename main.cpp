#include <QApplication>
#include "src/MainWindow.hpp"
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
