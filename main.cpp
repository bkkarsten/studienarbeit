#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "WindowManager.hpp"
#include "initialiseDirectory.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    
    QString dir = initialiseDirectory();
    WindowManager manager(dir);

    return app.exec();
}
