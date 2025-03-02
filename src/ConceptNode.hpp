#ifndef CONCEPTNODE_H
#define CONCEPTNODE_H

#include <QuickQanava>
#include <QDateTime>

#include "Content.hpp"

class ConceptNode : public qan::Node {
    Q_OBJECT
private:
    QDateTime lastChanged;
    QQuickItem* getContentItem() const;

CONTENTOWNER(content, getContentItem);

public:
    ConceptNode(const QString& contentTextForm = "");
    const QDateTime& getLastChanged() const { return lastChanged; }
    void* getOutgoingQuestions() const { return nullptr; } // TODO!
    /**
     * @brief Returns the QML item associated with this node type.
     */
    static QQmlComponent* delegate(QQmlEngine& engine, QObject* parent = nullptr);
};


#endif