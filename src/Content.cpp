#include "Content.hpp"

#include <QRegularExpression>
#include <QList>

#include <utility>

void Content::setTextForm(const QString& textForm) {
    this->textForm = textForm;
}

enum ContentType {
    text, image
};

/**
 * @brief Splits the given string into a list of substrings depending on whether they are text or
 * the "img" command
 */
QList<std::pair<QString, ContentType>> separate(const QString& string) {
    QList<std::pair<QString, ContentType>> result;
    QRegularExpression imgRegex(QString(IMAGE_CMD).append(R"(\([^()]+\.[^()]+\))"));
    QRegularExpressionMatchIterator it = imgRegex.globalMatch(string);

    int lastIndex = 0;
    while(it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        int matchStart = match.capturedStart();
        int matchEnd = match.capturedEnd();

        if(matchStart > lastIndex) {
            result.append({string.mid(lastIndex, matchStart - lastIndex), ContentType::text});
        }

        result.append({match.captured(), ContentType::image});

        lastIndex = matchEnd;
    }

    if (lastIndex < string.length()) {
        result.append({string.mid(lastIndex), ContentType::text});
    }

    return result;
}

QString Content::toQml() const {
    QList<std::pair<QString, ContentType>> elements = separate(textForm);
    QString qml("import QtQuick; Column { width:parent.width; height:parent.height; Text { id:notfound; color:\"red\"; text: \"Image(s) not found\"; visible:false}" );

    for(const auto& el : elements) {
        if(el.second == ContentType::text) {
            qml.append("Text { text: \"");
            QString escaped = el.first;
            escaped.replace('"', "\\\""); // replace " with \" for embedding in qml
            escaped.replace('\'', "\\'"); // replace ' with \' for embedding in qml
            qml.append(escaped);
            qml.append("\" } ");
        }
        else if(el.second == ContentType::image) {
            QString file = el.first.mid(4);
            file.removeLast();
            file.replace('\\', '/');
            file.replace('"', "\\\""); // replace " with \" for embedding in qml
            file.replace('\'', "\\'"); // replace ' with \' for embedding in qml
            qml.append("Image { width:parent.width; fillMode: Image.PreserveAspectFit; source: \"file:///");
            qml.append(file);
            qml.append("\"; onStatusChanged: { if(status == Image.Error) { notfound.visible = true; }}}");
        }
    }
    qml.append("}");
    return qml;
}