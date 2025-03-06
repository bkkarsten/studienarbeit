#ifndef RELATIONNODE_H
#define RELATIONNODE_H

#include "NodeBase.hpp"
#include "Question.hpp"

/**
 * @brief A node that acts as a relation between multiple source and target nodes.
 * As such, it is a question that has multiple concepts as context and multiple answers.
 */
class RelationNode : public NodeBase
                   , public Question
{
private:
    QQuickItem* getContentItem() override;
public:
    RelationNode(QObject* parent = nullptr);

    /**
     * @brief Returns the QML item associated with this node type.
     */
    static QQmlComponent* delegate(QQmlEngine& engine, QObject* parent = nullptr);

    QList<ConceptNode*> getContext() override;
    QList<ConceptNode*> getAnswers() override;
};


#endif