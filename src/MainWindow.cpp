#include "MainWindow.hpp"

#include <iostream>

#include <QQmlProperty>
#include <QQmlContext>

MainWindow::MainWindow()
    : engine()
    , openFileDialog()
    , errorMessage()
    , openedFile()
{
    // Setup engine
    engine.rootContext()->setContextProperty("window", this);
    engine.load(QUrl("qrc:/main.qml"));
    if (engine.rootObjects().isEmpty()) {
        throw std::runtime_error("Root object not found.");
    }

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
        showError("Root object not found.");
        return;
    }
    QObject* contentLoader = rootObject->findChild<QObject*>("loader");
    if (!contentLoader) {
        showWarning("Content loader not found.");
        return;
    }
    QQmlProperty::write(contentLoader, "source", source);
}

void MainWindow::updateContent() {
    if(openedGraph) {
        setContent("qrc:/file_loaded_placeholder.qml");
    }
    else {
        setContent("qrc:/no_file.qml");
    }
}

void MainWindow::showError(QString message) {
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.setWindowTitle(tr("Error"));
    errorMessage.setText(message);
    errorMessage.exec();
}

void MainWindow::showWarning(QString message) {
    errorMessage.setIcon(QMessageBox::Warning);
    errorMessage.setWindowTitle(tr("Warning"));
    errorMessage.setText(message);
    errorMessage.exec();
}

void MainWindow::registerChanges() {
    unsavedChanges = true;
}

void MainWindow::openFile() {
    if(!openFileDialog.exec()) {
        showError("Error opening file.");
        return;
    }
    QStringList fileNames = openFileDialog.selectedFiles();
    openedFile.open(fileNames.first().toStdString());
    if(!openedFile) {
        showError("Error opening file.");
        return;
    }
    openedGraph = true;
    updateContent();
}

void MainWindow::newFile() {}

void MainWindow::saveFile() {}

void MainWindow::saveFileAs() {}