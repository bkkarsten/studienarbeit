#include "ConceptNode.hpp"
#include "Question.hpp"
#include "EdgeBase.hpp"

QQuickItem* ConceptNode::getContentItem() {
    return getItem() ? getItem()->findChild<QQuickItem*>("content") : nullptr;
}

ConceptNode::ConceptNode(QObject* parent)
    : NodeBase(parent)
    , lastChanged(QDateTime::currentDateTime())
{
}

QQmlComponent* ConceptNode::delegate(QQmlEngine& engine, QObject* parent) {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> delegate;
    if (!delegate)
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/ConceptNode.qml");
    return delegate.get();
}

QList<Question*> ConceptNode::getOutgoingQuestions() {
    QList<Question*> result;
    for(qan::Edge* edge : qan::Node::get_out_edges()) {
        if(EdgeBase* edgeBase = dynamic_cast<EdgeBase*>(edge)) {
            result.append(edgeBase->getQuestion());
        }
    }
    return result;
}

QList<Question*> ConceptNode::getIncomingQuestions() {
    QList<Question*> result;
    for(qan::Edge* edge : qan::Node::get_in_edges()) {
        if(EdgeBase* edgeBase = dynamic_cast<EdgeBase*>(edge)) {
            result.append(edgeBase->getQuestion());
        }
    }
    return result;
}