#ifndef QUESTIONEDGE_H
#define QUESTIONEDGE_H

#include "EdgeBase.hpp"
#include "Question.hpp"

/**
 * @brief An edge in the graph that represents a question.
 */
class QuestionEdge : public EdgeBase
                   , public Question 
{
private:
    QQuickItem* getContentItem() override { return nullptr; }
public:
    QuestionEdge(QObject* parent) : EdgeBase(parent) {}
    /**
     * @brief Returns the QML item associated with this node type.
     */
    static QQmlComponent* delegate(QQmlEngine& engine, QObject* parent = nullptr);

    Question* getQuestion() override { return dynamic_cast<Question*>(this); }

    QList<ConceptNode*> getContext() override { return QList<ConceptNode*>(); }
    QList<ConceptNode*> getAnswers() override { return QList<ConceptNode*>(); }
};


#endif