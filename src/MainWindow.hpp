#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQmlApplicationEngine>

class MainWindow  {
private:
    QQmlApplicationEngine engine;
public:
    MainWindow();
    void setContent(QString source);
};

#endif