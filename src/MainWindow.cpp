#include "MainWindow.hpp"
#include "config.hpp"

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

MainWindow::MainWindow(QString defaultDir)
    : engine()
    , openFileDialog()
    , saveAsDialog()
    , errorMessage()
    , savePrompt()
    , openedFile()
    , openedFileName()
{
    // Setup engine
    engine.rootContext()->setContextProperty("window", this);
    engine.load(QUrl("qrc:/main.qml"));
    if (engine.rootObjects().isEmpty()) {
        throw std::runtime_error("Root object not found.");
    }
    qmlWindow = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    qmlWindow->setTitle(WINDOW_TITLE);

    // Configure file dialogs
    openFileDialog.setFileMode(QFileDialog::ExistingFile);
    openFileDialog.setNameFilter(tr("GraphML File (*.graphml)"));
    saveAsDialog.setFileMode(QFileDialog::AnyFile);
    saveAsDialog.setNameFilter(tr("GraphML File (*.graphml)"));
    saveAsDialog.setAcceptMode(QFileDialog::AcceptSave);
    if(!defaultDir.isEmpty()) {
        openFileDialog.setDirectory(QDir(defaultDir));
        saveAsDialog.setDirectory(QDir(defaultDir));
    }

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

QString MainWindow::updateWindowTitle() {
    QString newTitle = QString(WINDOW_TITLE);
    if(openedGraph) {
        newTitle.append(" - ");
        newTitle.append(openedFileName.isEmpty()? tr("unsaved Graph") : openedFileName.split("/").last());
    }
    if(unsavedChanges) {
        newTitle.append("*");
    }
    qmlWindow->setTitle(newTitle);
    return newTitle;
    

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
    updateWindowTitle();
}

void MainWindow::openFile() {
    SAVE_PROMPT_GUARD(
        if(!openFileDialog.exec()) {
            return;
        }
        std::string fileName = openFileDialog.selectedFiles().first().toStdString();
        std::fstream tempFile(fileName);
        if(!tempFile) {
            showError("Error opening new file.");
            return;
        }
        openedFile = std::move(tempFile);
        openedFileName = QString::fromStdString(fileName);
        openedGraph = true;
        updateWindowTitle();
        updateContent();
    )
}

void MainWindow::newFile() {
    SAVE_PROMPT_GUARD(
        openedFile.close();
        openedFile.clear();
        openedFileName.clear();
        openedGraph = true;
        unsavedChanges = false;
        std::cout << "new" << std::endl;
        // TODO

        updateWindowTitle();
        updateContent();
    )
}

void MainWindow::saveFile() {
    if(!openedGraph) {
        return;
    }
    if(openedFile.is_open()) {
        saveGraph();
    }
    else {
        saveFileAs();
    }
}

void MainWindow::saveFileAs() {
    if(!openedGraph) {
        return;
    }
    if(!saveAsDialog.exec()) {
        return;
    }
    std::string fileName = saveAsDialog.selectedFiles().first().toStdString();
    std::ofstream createFile(fileName);
    if(!createFile) {
        showError("Error creating file.");
        return;
    }
    createFile.close();
    std::fstream tempFile(fileName);
    if(!tempFile) {
        showError("Error opening new file.");
        return;
    }
    openedFile = std::move(tempFile);
    openedFileName = QString::fromStdString(fileName);
    saveGraph();
}

void MainWindow::saveGraph() {
    unsavedChanges = false;
    updateWindowTitle();
    std::cout << "saved" << std::endl;

    // TODO
}