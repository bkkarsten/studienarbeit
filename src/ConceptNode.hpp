#ifndef CONCEPTNODE_H
#define CONCEPTNODE_H

#include <QDateTime>

#include "Content.hpp"
#include "NodeBase.hpp"

class Question;

class ConceptNode : public NodeBase {
    Q_OBJECT
private:
    QDateTime lastChanged;
    boost::json::string getTypeName() override { return "ConceptNode"; }
    boost::json::object propertiesToJson() override;
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