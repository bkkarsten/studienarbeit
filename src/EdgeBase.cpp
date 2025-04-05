#include "EdgeBase.hpp"
#include "NodeBase.hpp"
#include "qanNodeItem.h"

boost::json::object EdgeBase::toJson(int srcId, int destId) {
    boost::json::object json = propertiesToJson();
    json["type"] = getTypeName();
    json["src"] = srcId;
    json["dest"] = destId;
    return json;
}

void EdgeBase::loadJson(boost::json::object json) {
    propertiesLoadJson(json);
}

bool EdgeBase::changeSource(QQuickItem* target) {
    qan::NodeItem* nodeItem = dynamic_cast<qan::NodeItem*>(target);
    if(nodeItem == nullptr) {
        return false;
    }
    NodeBase* node = dynamic_cast<NodeBase*>(nodeItem->getNode());
    if(node == nullptr || node == getDestination() || getGraph()->find_edge(node, getDestination()) != nullptr) {
        return false;
    }
    if(!validSource(node)) {
        return false;
    }
    set_src(node);
    getItem()->setSourceItem(nodeItem);
    emit anythingChanged();
    return true;
}

bool EdgeBase::changeDestination(QQuickItem* target) {
    qan::NodeItem* nodeItem = dynamic_cast<qan::NodeItem*>(target);
    if(nodeItem == nullptr) {
        return false;
    }
    NodeBase* node = dynamic_cast<NodeBase*>(nodeItem->getNode());
    if(node == nullptr || node == getSource() || getGraph()->find_edge(getSource(), node) != nullptr) {
        return false;
    }
    if(!validDestination(node)) {
        return false;
    }
    set_dst(node);
    getItem()->setDestinationItem(nodeItem);
    emit anythingChanged();
    return true;
}