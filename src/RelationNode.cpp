#include "RelationNode.hpp"
#include "ConnectorEdge.hpp"
#include "ConceptNode.hpp"

RelationNode::RelationNode(QObject* parent) 
    : NodeBase(parent)
    , Question()
{
}

QQmlComponent* RelationNode::delegate(QQmlEngine& engine, QObject* parent) {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> delegate;
    if (!delegate)
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/RelationNode.qml");
    return delegate.get();
}

QList<ConceptNode*> RelationNode::getContext() {
    QList<ConceptNode*> context;
    for(const auto& edge : get_in_edges()) {
        ConnectorEdge* conn = dynamic_cast<ConnectorEdge*>(edge);
        if(conn == nullptr) continue;
        qan::Node* src = conn->getSource();
        if(src == nullptr) continue;
        ConceptNode* conc = dynamic_cast<ConceptNode*>(src);
        if(conc == nullptr) continue;
        context.append(conc);
    }
    return context;
}

QList<ConceptNode*> RelationNode::getAnswers() {
    QList<ConceptNode*> answers;
    for(const auto& edge : get_out_edges()) {
        ConnectorEdge* conn = dynamic_cast<ConnectorEdge*>(edge);
        if(conn == nullptr) continue;
        qan::Node* dest = conn->getDestination();
        if(dest == nullptr) continue;
        ConceptNode* conc = dynamic_cast<ConceptNode*>(dest);
        if(conc == nullptr) continue;
        answers.append(conc);
    }
    return answers;
}

QQuickItem* RelationNode::getContentItem() {
    return getItem() ? getItem()->findChild<QQuickItem*>("content") : nullptr;
}

boost::json::object RelationNode::propertiesToJson() {
    return Question::questionToJson();
}
