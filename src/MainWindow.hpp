#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>

#include <QQmlApplicationEngine>
#include <QFileDialog>


/**
 * @brief Main window of the application which handles the QML
 */
class MainWindow : public QObject {
    Q_OBJECT
private:
    // QML engine
    QQmlApplicationEngine engine;
    // File dialog configured to be used to open files
    QFileDialog openFileDialog;
    // The file which has been opened
    std::fstream openedFile;
    // Whether a graph is currently opened
    bool openedGraph = false;
    /**
     * @brief Sets the window's core QML content.
     * @param source The qml file to load
     */
    void setContent(QString source);
    /** 
     * @brief Updates the window's core QML content based on whether a graph is opened and which.
     */
    void updateContent();
public:
    MainWindow();
    ~MainWindow();
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