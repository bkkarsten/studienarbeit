#ifndef CONTENTOWNER_H
#define CONTENTOWNER_H

#include <QString>
#include <QQuickItem>
#include <QStringList>
#include <QPair>

// The sequence of characters that indicates an image
#define IMAGE_CMD "img"

/**
 * @brief Content for QML elements that is represented by text. Can be applied to Content.qml items.
 * 
 * Images can be created in the text by using the img(<path>) command.
 */
class Content {
private:
    QString textForm;
    /**
     * @brief Splits the given string into a list of substrings depending on whether they are text or
     * the "img" command.
     */
    QPair<QStringList, QStringList> separate(const QString& string) const;
public:
    Content() = default;

    const QString& getTextForm() const { return textForm; }
    
    /**
     * @brief Seperates the text representation and applies it to the given content item of type Content.qml.
     */
    void apply(QQuickItem* contentItem) const;
    
    void setTextForm(const QString& textForm, QQuickItem* contentItem = nullptr);
};

#endif