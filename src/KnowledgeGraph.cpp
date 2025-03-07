#include "KnowledgeGraph.hpp"
#include "NodeBase.hpp"
#include "EdgeBase.hpp"


bool KnowledgeGraph::valid() {
    for(qan::Node* node : get_nodes()) {
        NodeBase* nodeBase = dynamic_cast<NodeBase*>(node);
        if(!nodeBase) {
            return false;
        }
        if(!nodeBase->valid()) {
            return false;
        }
    }
    for(qan::Edge* edge : get_edges()) {
        EdgeBase* edgeBase = dynamic_cast<EdgeBase*>(edge);
        if(!edgeBase) {
            return false;
        }
        if(!edgeBase->valid()) {
            return false;
        }
    }
    return true;
}

ConceptNode* KnowledgeGraph::insertConceptNode(QString contentTextForm, qreal x, qreal y, qreal width, qreal height) {
    ConceptNode* node = insertNode<ConceptNode>();
    if(!node) {
        return nullptr;
    }
    node->setContentTextForm(contentTextForm);
    qan::NodeItem* item = node->getItem();
    if(item != nullptr) {
        item->setX(x);
        item->setY(y);
        if(width > 0) {
            item->setWidth(width);
        }
        if(height > 0) {
            item->setHeight(height);
        }
    }
    return node;
}

QuestionEdge* KnowledgeGraph::insertQuestionEdge(QString contentTextForm, ConceptNode* src, ConceptNode* dest) {
    QuestionEdge* edge = dynamic_cast<QuestionEdge*>(insertEdge<QuestionEdge>(*src, dest));
    if(edge) {
        edge->setContentTextForm(contentTextForm);
    }
    return edge;
}

ConnectorEdge* KnowledgeGraph::insertConnectorEdge(ConceptNode* src, RelationNode* dest) {
    return dynamic_cast<ConnectorEdge*>(insertEdge<ConnectorEdge>(*src, dest));
}

ConnectorEdge* KnowledgeGraph::insertConnectorEdge(RelationNode* src, ConceptNode* dest) {
    return dynamic_cast<ConnectorEdge*>(insertEdge<ConnectorEdge>(*src, dest));
}

RelationNode* KnowledgeGraph::insertRelationNode(QString contentTextForm, qreal x, qreal y, qreal width, qreal height, QList<ConceptNode*> context, QList<ConceptNode*> answers) {
    RelationNode* node = insertNode<RelationNode>();
    if(!node) {
        return nullptr;
    }
    node->setContentTextForm(contentTextForm);
    qan::NodeItem* item = node->getItem();
    if(item != nullptr) {
        item->setX(x);
        item->setY(y);
        if(width > 0) {
            item->setWidth(width);
        }
        if(height > 0) {
            item->setHeight(height);
        }
    }
    for(ConceptNode* c : context) {
        ConnectorEdge* edge = insertConnectorEdge(c, node);
    }
    for(ConceptNode* a : answers) {
        ConnectorEdge* edge = insertConnectorEdge(node, a);
    }
    return node;
}
