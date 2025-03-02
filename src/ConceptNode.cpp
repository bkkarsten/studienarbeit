#include "ConceptNode.hpp"

QQuickItem* ConceptNode::getContentItem() const
{
    return getItem() ? getItem()->findChild<QQuickItem*>("content") : nullptr;
}

ConceptNode::ConceptNode(const QString& contentTextForm)
    : lastChanged(QDateTime::currentDateTime())
{
}

QQmlComponent* ConceptNode::delegate(QQmlEngine& engine, QObject* parent) {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> delegate;
    if (!delegate)
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/ConceptNode.qml");
    return delegate.get();
}