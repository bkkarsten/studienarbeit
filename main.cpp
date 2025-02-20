#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "MainWindow.hpp"
#include "initialiseDirectory.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    
    QString dir = initialiseDirectory();
    MainWindow window(dir);

    return app.exec();
}
