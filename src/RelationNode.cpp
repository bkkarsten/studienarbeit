#include "RelationNode.hpp"

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

QQuickItem* RelationNode::getContentItem() {
    return getItem() ? getItem()->findChild<QQuickItem*>("content") : nullptr;
}