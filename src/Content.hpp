#ifndef CONTENT_H
#define CONTENT_H

#include <QString>

// The sequence of characters that indicates an image
#define IMAGE_CMD "img"

/**
 * @brief Represents the content of a node or edge in a graph. It is specified by the user via text,
 * but can generate QML content based on that.
 */
class Content {
private:
    // The text representation of the content.
    QString textForm;
public:
    Content() : textForm() {}
    Content(const QString& textForm) : textForm(textForm) {}
    const QString& getTextForm() const { return textForm; }
    void setTextForm(const QString& textForm);
    /**
     * @brief: Generates a QML representation of the content, resolving "img(<file>)".
     */
    QString toQml() const;
};

#endif