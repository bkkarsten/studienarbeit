#include "Content.hpp"

#include <QRegularExpression>
#include <QMetaObject>

QPair<QStringList, QStringList> Content::separate(const QString& string) const {
    QStringList elements;
    QStringList types;
    QRegularExpression imgRegex(QString(IMAGE_CMD).append(R"(\([^()]+\.[^()]+\))"));
    QRegularExpressionMatchIterator it = imgRegex.globalMatch(string);

    int lastIndex = 0;
    while(it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        int matchStart = match.capturedStart();
        int matchEnd = match.capturedEnd();

        if(matchStart > lastIndex) {
            QString text = string.mid(lastIndex, matchStart - lastIndex);
            if(text[0] == '\n') {
                text.remove(0, 1);
            }
            elements.append(text);
            types.append("text");
        }

        QString file = match.captured().mid(QString(IMAGE_CMD).length() + 1);
        file.removeLast();
        elements.append(file);
        types.append("image");

        lastIndex = matchEnd;
    }

    if (lastIndex < string.length()) {
        QString text = string.mid(lastIndex);
        if(text[0] == '\n') {
            text.remove(0, 1);
        }
        elements.append(text);
        types.append("text");
    }

    return {elements, types};
}


void Content::apply(QQuickItem* contentItem) const 
{
    QPair<QStringList, QStringList> separation = separate(textForm);
    if(!contentItem) {
        return;
    }
    bool success = QMetaObject::invokeMethod(contentItem, "setElements", 
        Q_ARG(QVariant, QVariant::fromValue(separation.first)), 
        Q_ARG(QVariant, QVariant::fromValue(separation.second)) 
    );
    if(!success) {
        qWarning() << "ContentOwner did not find setElements method in the specified content item!";
    }
}

void Content::setTextForm(const QString& textForm, QQuickItem* contentItem) { 
    this->textForm = textForm; 
    if(contentItem) {
        apply(contentItem);
    }
}
