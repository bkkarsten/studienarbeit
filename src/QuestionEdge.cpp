#include "QuestionEdge.hpp"
#include "ConceptNode.hpp"

QQmlComponent* QuestionEdge::delegate(QQmlEngine& engine, QObject* parent) {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> delegate;
    if (!delegate)
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/QuestionEdge.qml");
    return delegate.get();
}

QQuickItem* QuestionEdge::getContentItem() {
    return getItem() ? getItem()->findChild<QQuickItem*>("content") : nullptr;
}

boost::json::object QuestionEdge::propertiesToJson() {
    return Question::questionToJson();
}

void QuestionEdge::propertiesLoadJson(boost::json::object json) {
    Question::questionLoadJson(json);
}

QList<ConceptNode*> QuestionEdge::getContext() {
    ConceptNode* source = dynamic_cast<ConceptNode*>(qan::Edge::getSource());
    if(source) {
        return QList<ConceptNode*>({source});
    }
    return QList<ConceptNode*>();
}

QList<ConceptNode*> QuestionEdge::getAnswers() {
    ConceptNode* source = dynamic_cast<ConceptNode*>(qan::Edge::getDestination());
    if(source) {
        return QList<ConceptNode*>({source});
    }
    return QList<ConceptNode*>();
}