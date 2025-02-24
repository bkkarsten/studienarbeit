#include "initialiseDirectory.hpp"
#include "config.hpp"

#include <QStandardPaths>
#include <QDir> 

QString initialiseDirectory() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + QString::fromStdString(GRAPH_DIRECTORY);
    QDir dir(path);
    if(!dir.exists()) {
        dir.mkpath(path);
    }
    return path;
}