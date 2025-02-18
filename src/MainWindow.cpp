#include "MainWindow.hpp"
#include <QQmlProperty>

MainWindow::MainWindow()
    : engine()
{
    setContent("qrc:/no_file.qml");
}

void MainWindow::setContent(QString source) {
    QObject* contentLoader = engine.rootObjects().first()->findChild<QObject*>("contentLoader");
    if (contentLoader) {
        QQmlProperty::write(contentLoader, "source", source);
    }
}