#include "MainWindow.hpp"
#include <QQmlProperty>
#include <QQmlContext>
#include <iostream>

MainWindow::MainWindow()
    : engine()
    , openFileDialog()
    , openedFile()
{
    // Setup engine
    engine.rootContext()->setContextProperty("window", this);
    engine.load(QUrl("qrc:/main.qml"));

    // exception werfen wenn rootObject empty


    // Configure file dialogs
    openFileDialog.setFileMode(QFileDialog::ExistingFile);
    openFileDialog.setNameFilter(tr("GraphML File (*.graphml)"));
}

MainWindow::~MainWindow() {
    openedFile.close();
}

void MainWindow::setContent(QString source) {
    QObject* rootObject = engine.rootObjects().first();
    if (!rootObject) {
        return;
    }
    QObject* contentLoader = rootObject->findChild<QObject*>("loader");
    if (contentLoader) {
        QQmlProperty::write(contentLoader, "source", source);
    }
}

void MainWindow::updateContent() {
    if(openedGraph) {
        setContent("qrc:/file_loaded_placeholder.qml");
    }
    else {
        setContent("qrc:/no_file.qml");
    }
}

void MainWindow::openFile() {
    if(!openFileDialog.exec()) {
        return;
    }
    QStringList fileNames = openFileDialog.selectedFiles();
    openedFile.open(fileNames.first().toStdString());
    if(!openedFile) {
        return;
    }
    openedGraph = true;
    updateContent();
}

void MainWindow::newFile() {}

void MainWindow::saveFile() {}

void MainWindow::saveFileAs() {}