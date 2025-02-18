#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>

#include <QQmlApplicationEngine>
#include <QFileDialog>

class MainWindow : public QObject {
    Q_OBJECT
private:
    QQmlApplicationEngine engine;
    QFileDialog openFileDialog;
    std::fstream openedFile;
    bool openedGraph = false;
public:
    MainWindow();
    ~MainWindow();
    void setContent(QString source);
    void updateContent();
    Q_INVOKABLE void newFile();
    Q_INVOKABLE void openFile();
    Q_INVOKABLE void saveFile();
    Q_INVOKABLE void saveFileAs();
};

#endif