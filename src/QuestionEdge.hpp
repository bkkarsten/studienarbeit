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

    bool validSource(NodeBase* src) override;
    bool validDestination(NodeBase* dest) override;

    void emitContentChangedSignal() override { emit contentChanged(); emit anythingChanged(); }
    void emitWeightChangedSignal() override { emit weightChanged(); emit anythingChanged(); }
signals:
    void contentChanged();
    void weightChanged();

public:
    Q_PROPERTY(QString contentTextForm READ getContentTextForm WRITE setContentTextForm NOTIFY contentChanged);
    Q_PROPERTY(qreal customWeight READ getCustomWeight WRITE setCustomWeight NOTIFY weightChanged);
    
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