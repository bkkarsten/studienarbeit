#ifndef KEYBOARDHELPER_H
#define KEYBOARDHELPER_H

#include <QObject>
#include <QGuiApplication>
#include <qqml.h>

class KeyboardHelper : public QObject {
    Q_OBJECT
    QML_ELEMENT
public:
    Q_INVOKABLE static int modifiers();

};

QML_DECLARE_TYPE(KeyboardHelper)

#endif