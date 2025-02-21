#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "config.hpp"
#include "WindowManager.hpp"
#include "initialiseDirectory.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QQuickStyle::setStyle(STYLE_TEMPLATE);
    
    QString dir = initialiseDirectory();
    WindowManager manager(dir);

    return app.exec();
}
