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
    QPair<QStringList, QStringList> separate(const QString& string);
    /**
     * @brief Seperates the text representation and applies it to the given content item of type Content.qml.
     */
    void apply(QQuickItem* contentItem);
public:
    Content() = default;

    const QString& getTextForm() const { return textForm; }
    
    void setTextForm(const QString& textForm, QQuickItem* contentItem = nullptr);
};

/**
 * @brief Macro that can be used in a class to give it functionality for managing Content.
 * @param content_member The name of the member variable that will store the Content object.
 * @param get_content_item A method that returns the QQuickItem that represents the content.
 */
#define CONTENTOWNER(content_member, get_content_item) \
private: \
    Content content_member; \
public: \
    const QString& getContentTextForm() const { return content_member.getTextForm(); } \
    void setContentTextForm(const QString& textForm) { content_member.setTextForm(textForm, get_content_item()); }


#endif