#include "MainWindow.hpp"

#include <iostream>

#include <QQmlProperty>
#include <QQmlContext>
#include <QPushButton>

/**
 * @brief If there are any unsaved changes, this will open a save dialog and execute the given code 
 * only if the user does not click "cancel".
 * @param code The code that is executed if cancel is not clicked.
 */
#define SAVE_PROMPT_GUARD(code) \
    if(unsavedChanges) { \
        savePrompt.exec(); \
        int res = savePrompt.result(); \
        if(res != QMessageBox::Cancel) { \
            code \
        } \
    } \
    else { \
        code \
    } 

MainWindow::MainWindow()
    : engine()
    , openFileDialog()
    , errorMessage()
    , savePrompt()
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

    // Confige save prompt dialog
    savePrompt.setWindowTitle(tr("Unsaved Changes"));
    savePrompt.setIcon(QMessageBox::Question);
    savePrompt.setText(tr("There are unsaved changes. How will you proceed?"));
    savePrompt.addButton(QMessageBox::Cancel);
    QPushButton* saveButton = savePrompt.addButton(QMessageBox::Save);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    savePrompt.addButton(QMessageBox::Discard);
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
    SAVE_PROMPT_GUARD(
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
    )
}

void MainWindow::newFile() {
    SAVE_PROMPT_GUARD(
        openedFile.close();
        openedGraph = true;
        unsavedChanges = false;

        // TODO

        updateContent();
    )
}

void MainWindow::saveFile() {
    unsavedChanges = false;
    std::cout << "saved" << std::endl;

    // TODO!
}

void MainWindow::saveFileAs() {}