#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>

#include <QQmlApplicationEngine>
#include <QFileDialog>
#include <QMessageBox>
#include <QQuickWindow>


/**
 * @brief Main window of the application which handles the QML
 */
class MainWindow : public QObject {
    Q_OBJECT
private:
    // QML engine
    QQmlApplicationEngine engine;
    // The ApplicationWindow defined in QML
    QQuickWindow* qmlWindow;
    // File dialog configured to be used to open files
    QFileDialog openFileDialog;
    // File dialog configured to be used to save files
    QFileDialog saveAsDialog;
    // An object to show any error message
    QMessageBox errorMessage;
    // An object to show a prompt to save changes
    QMessageBox savePrompt;
    // The file which has been opened
    std::fstream openedFile;
    // The name of the file which has been opened
    QString openedFileName;
    // Whether a graph is currently opened
    bool openedGraph = false;
    // Whether there are any unsaved changes
    bool unsavedChanges = false;
    /**
     * @brief Sets the window's core QML content.
     * @param source The qml file to load
     */
    void setContent(QString source);
    /** 
     * @brief Updates the window's core QML content based on whether a graph is opened and which.
     */
    void updateContent();
    /**
     * @brief Updates the window's title based on the opened file.
     * @return The new window title.
     */
    QString updateWindowTitle();
    /**
     * @brief Shows an error message box with the given message.
     */
    void showError(QString message);
    /**
     * @brief Shows a warning message box with the given message.
     */
    void showWarning(QString message);
    /**
     * @brief Saves the graph to openedFile.
     */
    void saveGraph();
public:
    /**
     * @brief Constructs the main window.
     * @param defaultDir The default directory to open file dialogs in. If empty, will open in the executable's directory.
     */ 
    MainWindow(QString defaultDir = "");
    ~MainWindow();

    /**
     * @brief Lets the main window know that changes have been made to the opened graph.
     */
    Q_INVOKABLE void registerChanges();
    /**
     * @brief Creates a new graph. 
     * 
     * Called when clicking File->New in the menu bar. 
     */
    Q_INVOKABLE void newFile();
    /**
     * @brief Opens a graph from an existing file selected in a file dialog.
     * 
     * Called when clicking File->Open in the menu bar. 
     */
    Q_INVOKABLE void openFile();
    /**
     * @brief Saves the open graph to the file associated with it.
     * 
     * Called when clicking File->Save in the menu bar. 
     */
    Q_INVOKABLE void saveFile();
    /**
     * @brief Saves the open graph to a (possibly new) file selected in a file dialog.
     * 
     * Called when clicking File->Save As in the menu bar. 
     */
    Q_INVOKABLE void saveFileAs();
};

#endif