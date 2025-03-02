#include "QuestionEdge.hpp"

QQmlComponent* QuestionEdge::delegate(QQmlEngine& engine, QObject* parent) {
    Q_UNUSED(parent)
    static std::unique_ptr<QQmlComponent> delegate;
    if (!delegate)
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/QuestionEdge.qml");
    return delegate.get();
}