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
    Q_OBJECT
private:
    QQuickItem* getContentItem() override;
    boost::json::object propertiesToJson() override;
    void propertiesLoadJson(boost::json::object json) override;
    void emitContentChangedSignal() override { emit contentChanged(); emit anythingChanged(); }
    void emitWeightChangedSignal() override { emit weightChanged(); emit anythingChanged(); }
signals:
    void contentChanged();
    void weightChanged();

public:
    Q_PROPERTY(QString contentTextForm READ getContentTextForm WRITE setContentTextForm NOTIFY contentChanged);
    Q_PROPERTY(qreal customWeight READ getCustomWeight WRITE setCustomWeight NOTIFY weightChanged);

    RelationNode(QObject* parent = nullptr);

    boost::json::string getTypeName() override { return "RelationNode"; }
    /**
     * @brief Returns the QML item associated with this node type.
     */
    static QQmlComponent* delegate(QQmlEngine& engine, QObject* parent = nullptr);

    QList<ConceptNode*> getContext() override;
    QList<ConceptNode*> getAnswers() override;
};


#endif