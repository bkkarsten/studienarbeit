#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include <boost/json/src.hpp>

#include "config.hpp"
#include "WindowManager.hpp"
#include "initialiseDirectory.hpp"
#include "KeyboardHelper.hpp"
#include "KnowledgeGraph.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QQuickStyle::setStyle(STYLE_TEMPLATE);

    qmlRegisterType<KnowledgeGraph>("studar", 1, 0, "KnowledgeGraph");
    qmlRegisterSingletonType<KeyboardHelper>("studar", 1, 0, "KeyboardHelper", [](QQmlEngine*, QJSEngine*) -> QObject* {
        return new KeyboardHelper();
    });
    
    QString dir = initialiseDirectory();
    WindowManager manager(dir);

    return app.exec();
}
