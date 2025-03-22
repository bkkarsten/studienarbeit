#include "ConnectorEdge.hpp"
#include "ConceptNode.hpp"
#include "RelationNode.hpp"

bool ConnectorEdge::valid() {
    qan::Node* src = getSource();
    qan::Node* dest = getDestination();
    return (
        bool(dynamic_cast<ConceptNode*>(src))
      ^ bool(dynamic_cast<ConceptNode*>(dest))
    ) && (
        bool(dynamic_cast<RelationNode*>(src))
      ^ bool(dynamic_cast<RelationNode*>(dest))
    )
    && src != nullptr && dest != nullptr;
}

Question* ConnectorEdge::getQuestion() {
    qan::Node* src = getSource();
    if(dynamic_cast<RelationNode*>(src)) {
        return dynamic_cast<Question*>(src);
    }
    qan::Node* dest = getDestination();
    if(dynamic_cast<RelationNode*>(dest)) {
        return dynamic_cast<Question*>(dest);
    }
    return nullptr;
}

bool ConnectorEdge::validSource(NodeBase* src) {
    ConceptNode* conceptSrc = dynamic_cast<ConceptNode*>(src);
    RelationNode* relationSrc = dynamic_cast<RelationNode*>(src);
    ConceptNode* conceptDest = dynamic_cast<ConceptNode*>(getDestination());
    RelationNode* relationDest = dynamic_cast<RelationNode*>(getDestination());
    return (conceptSrc && relationDest) || (relationSrc && conceptDest);
}

bool ConnectorEdge::validDestination(NodeBase* dest) {
    ConceptNode* conceptDest = dynamic_cast<ConceptNode*>(dest);
    RelationNode* relationDest = dynamic_cast<RelationNode*>(dest);
    ConceptNode* conceptSrc = dynamic_cast<ConceptNode*>(getSource());
    RelationNode* relationSrc = dynamic_cast<RelationNode*>(getSource());
    return (conceptSrc && relationDest) || (relationSrc && conceptDest);
}