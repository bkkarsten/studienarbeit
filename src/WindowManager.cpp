#include "WindowManager.hpp"
#include "config.hpp"

#include "KnowledgeGraph.hpp"

#include <QQmlProperty>
#include <QQmlContext>
#include <QPushButton>
#include <QDebug>
#include <QuickQanava>


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
            unsavedChanges = false; \
            code \
            unsavedChanges = false; \
        } \
    } \
    else { \
        code \
    } 

WindowManager::WindowManager(QString defaultDir)
    : engine()
    , openFileDialog()
    , saveAsDialog()
    , errorMessage()
    , savePrompt()
    , openedFile()
    , openedFileName()
{
    // Setup engine
    engine.rootContext()->setContextProperty("manager", this);
    engine.load(QUrl("qrc:/main.qml"));
    if (engine.rootObjects().isEmpty()) {
        throw std::runtime_error("Root object not found.");
    }
    engine.addImportPath("external/QuickQanava/src");
    QuickQanava::initialize(&engine);
    qmlWindow = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    qmlWindow->setTitle(WINDOW_TITLE);

    // Configure file dialogs
    openFileDialog.setFileMode(QFileDialog::ExistingFile);
    openFileDialog.setNameFilter(tr("JSON File (*.json)"));
    saveAsDialog.setFileMode(QFileDialog::AnyFile);
    saveAsDialog.setNameFilter(tr("JSON File (*.json)"));
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
    connect(saveButton, &QPushButton::clicked, this, &WindowManager::saveFile);
    savePrompt.addButton(QMessageBox::Discard);
}

void WindowManager::setView(QString source) {
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

void WindowManager::updateView() {
    if(openedGraph) {
        // setView("qrc:/file_loaded_placeholder.qml");
        setView("qrc:/graphview.qml");
    }
    else {
        setView("qrc:/no_file.qml");
    }
}

void WindowManager::updateGraph() {
    if(openedGraph) {
        graph = qobject_cast<KnowledgeGraph*>(engine.rootObjects().first()->findChild<QQuickItem*>("graph"));
        if (graph) {
            connect(graph, &KnowledgeGraph::customElementInserted, this, &changesMade);
            connect(graph, &KnowledgeGraph::nodeRemoved, this, &changesMade);
            connect(graph, &KnowledgeGraph::onEdgeRemoved, this, &changesMade);
            connect(graph, &KnowledgeGraph::nodeMoved, this, &changesMade);
            connect(graph, &KnowledgeGraph::nodeResized, this, &changesMade);
            connect(graph, &KnowledgeGraph::elementChanged, this, &changesMade);
        }
    }
    else {
        graph = nullptr;
    }
}

QString WindowManager::updateWindowTitle() {
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

void WindowManager::showError(QString message) {
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.setWindowTitle(tr("Error"));
    errorMessage.setText(message);
    errorMessage.exec();
}

void WindowManager::showWarning(QString message) {
    errorMessage.setIcon(QMessageBox::Warning);
    errorMessage.setWindowTitle(tr("Warning"));
    errorMessage.setText(message);
    errorMessage.exec();
}

void WindowManager::registerChanges() {
    unsavedChanges = true;
    updateWindowTitle();
}

void WindowManager::openFile() {
    SAVE_PROMPT_GUARD(
        if(!openFileDialog.exec()) {
            return;
        }
        std::string fileName = openFileDialog.selectedFiles().first().toStdString();
        std::ifstream file(fileName);
        if(!file) {
            showError("Error opening file.");
            return;
        }
        openedFile = true;
        openedFileName = QString::fromStdString(fileName);
        openedGraph = true;
        updateView();
        updateGraph();
        graph->loadFile(file);
        file.close();
        unsavedChanges = false;
        updateWindowTitle();
    )
}

void WindowManager::newFile() {
    SAVE_PROMPT_GUARD(
        openedFile = false;
        openedFileName.clear();
        openedGraph = true;
        unsavedChanges = false;
        
        updateWindowTitle();
        updateView();
        updateGraph();

        graph->clearGraph();
    )
}

void WindowManager::saveFile() {
    if(!openedGraph) {
        return;
    }
    if(openedFile) {
        std::ofstream file(openedFileName.toStdString(), std::ios::trunc);
        saveGraph(file);
    }
    else {
        saveFileAs();
    }
}

void WindowManager::saveFileAs() {
    if(!openedGraph) {
        return;
    }
    if(!saveAsDialog.exec()) {
        return;
    }
    std::string fileName = saveAsDialog.selectedFiles().first().toStdString();
    std::ofstream file(fileName, std::ios::trunc);
    if(!file) {
        showError("Error opening new file.");
        return;
    }
    openedFile = true;
    openedFileName = QString::fromStdString(fileName);
    saveGraph(file);
}

void WindowManager::saveGraph(std::ofstream& file) {
    unsavedChanges = false;
    updateWindowTitle();
    graph->saveFile(file);
    file.close();
}

void WindowManager::closeFile() {
    SAVE_PROMPT_GUARD(
        openedFile = false;
        openedFileName.clear();
        openedGraph = false;
        unsavedChanges = false;
        updateWindowTitle();
        updateView();
        updateGraph();
    )
}

bool WindowManager::checkClose() {
    SAVE_PROMPT_GUARD(return true;)
    return false;
}

void WindowManager::changesMade() {
    unsavedChanges = true;
    updateWindowTitle();
}