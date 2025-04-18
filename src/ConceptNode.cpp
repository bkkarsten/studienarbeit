#include "ConceptNode.hpp"
#include "Question.hpp"
#include "EdgeBase.hpp"

boost::json::object ConceptNode::propertiesToJson() {
    boost::json::object json;
    json["lastChanged"] = lastChanged.toString().toStdString();
    json["content"] = getContentTextForm().toStdString();
    return json;
}

void ConceptNode::propertiesLoadJson(boost::json::object json) {
    lastChanged = QDateTime::fromString(QString::fromStdString(std::string(json["lastChanged"].as_string())), Qt::ISODate);
    setContentTextForm(QString::fromStdString(std::string(json["content"].as_string())));
}

QQuickItem* ConceptNode::getContentItem() {
    return getItem() ? getItem()->findChild<QQuickItem*>("content") : nullptr;
}

ConceptNode::ConceptNode(QObject* parent)
    : NodeBase(parent)
    , lastChanged(QDateTime::currentDateTime())
{
}

void ConceptNode::setContentTextForm(const QString &textForm) { 
    bool changes = (textForm != getContentTextForm()); 
    content.setTextForm(textForm, getContentItem()); 
    if(changes) { 
        changed();
    } 
} 

QQmlComponent* ConceptNode::delegate(QQmlEngine& engine, QObject* parent) {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> delegate;
    if (!delegate)
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/ConceptNode.qml");
    return delegate.get();
}

void ConceptNode::changed() {
    lastChanged = QDateTime::currentDateTime();
    emit contentChanged();
    emit anythingChanged();
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