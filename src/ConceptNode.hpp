#ifndef CONCEPTNODE_H
#define CONCEPTNODE_H

#include <QuickQanava>
#include <QDateTime>

#include "Content.hpp"

class Question;

class ConceptNode : public qan::Node {
    Q_OBJECT
private:
    QDateTime lastChanged;
    QQuickItem* getContentItem();

CONTENTOWNER(content, getContentItem);

public:
    ConceptNode(QObject* parent = nullptr);
    const QDateTime& getLastChanged() const { return lastChanged; }
    QList<Question*> getOutgoingQuestions();
    QList<Question*> getIncomingQuestions();
    /**
     * @brief Returns the QML item associated with this node type.
     */
    static QQmlComponent* delegate(QQmlEngine& engine, QObject* parent = nullptr);
};


#endif