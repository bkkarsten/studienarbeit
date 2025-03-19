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
    Q_OBJECT
private:
    QQuickItem* getContentItem() override;
    boost::json::object propertiesToJson() override;
    void propertiesLoadJson(boost::json::object json) override;
signals:
    void contentChanged();

public:
    Q_PROPERTY(QString contentTextForm READ getContentTextForm WRITE setContentTextForm NOTIFY contentChanged);
    
    QuestionEdge(QObject* parent = nullptr) : EdgeBase(parent) {}
    
    boost::json::string getTypeName() override { return "QuestionEdge"; }
    /**
     * @brief Returns the QML item associated with this node type.
     */
    static QQmlComponent* delegate(QQmlEngine& engine, QObject* parent = nullptr);

    Question* getQuestion() override { return dynamic_cast<Question*>(this); }

    QList<ConceptNode*> getContext() override;
    QList<ConceptNode*> getAnswers() override;
};


#endif