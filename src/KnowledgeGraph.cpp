#include "KnowledgeGraph.hpp"
#include "NodeBase.hpp"
#include "EdgeBase.hpp"

#include <fstream>
#include <type_traits>

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

template<typename NodeType>
requires HasContentChangedSignal<NodeType>
NodeType* KnowledgeGraph::insertCustomNode() {
    NodeType* node = insertNode<NodeType>();
    if(node != nullptr) {
        connect(node, &NodeType::contentChanged, this, [&](){ emit contentEdited(); });
    }
    return node;
}
template<typename NodeType>
requires (!HasContentChangedSignal<NodeType>)
NodeType* KnowledgeGraph::insertCustomNode() {
    NodeType* node = insertNode<NodeType>();
    return node;
}

template<typename EdgeType>
requires HasContentChangedSignal<EdgeType>
EdgeType* KnowledgeGraph::insertCustomEdge(qan::Node* src, qan::Node* dest) {
    EdgeType* edge = dynamic_cast<EdgeType*>(insertEdge<EdgeType>(*src, dest));
    if(edge != nullptr) {
        connect(edge, &EdgeType::contentChanged, this, [&](){ emit contentEdited(); });
    }
    return edge;
}
template<typename EdgeType>
requires (!HasContentChangedSignal<EdgeType>)
EdgeType* KnowledgeGraph::insertCustomEdge(qan::Node* src, qan::Node* dest) {
    EdgeType* edge = dynamic_cast<EdgeType*>(insertEdge<EdgeType>(*src, dest));
    return edge;
}

ConceptNode* KnowledgeGraph::insertConceptNode(QString contentTextForm, qreal x, qreal y, qreal width, qreal height) {
    ConceptNode* node = insertCustomNode<ConceptNode>();
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
    emit customElementInserted();
    return node;
}

QuestionEdge* KnowledgeGraph::insertQuestionEdge(ConceptNode* src, ConceptNode* dest, QString contentTextForm) {
    QuestionEdge* edge = insertCustomEdge<QuestionEdge>(src, dest);
    if(edge) {
        edge->setContentTextForm(contentTextForm);
    }
    emit customElementInserted();
    return edge;
}

ConnectorEdge* KnowledgeGraph::insertConnectorEdge(ConceptNode* src, RelationNode* dest) {
    emit customElementInserted();
    return insertCustomEdge<ConnectorEdge>(src, dest);
}

ConnectorEdge* KnowledgeGraph::insertConnectorEdge(RelationNode* src, ConceptNode* dest) {
    emit customElementInserted();
    return insertCustomEdge<ConnectorEdge>(src, dest);
}

EdgeBase* KnowledgeGraph::insertCorrectEdge(NodeBase* src, NodeBase* dest) {
    if(find_edge(src, dest) != nullptr) {
        return nullptr; // prevent insertion of dupliate edges
    }
    ConceptNode* conceptSrc = dynamic_cast<ConceptNode*>(src);
    ConceptNode* conceptDest = dynamic_cast<ConceptNode*>(dest);
    RelationNode* relationSrc = dynamic_cast<RelationNode*>(src);
    RelationNode* relationDest = dynamic_cast<RelationNode*>(dest);
    if(conceptSrc && conceptDest) {
        return insertQuestionEdge(conceptSrc, conceptDest);
    }
    else if(conceptSrc && relationDest) {
        return insertConnectorEdge(conceptSrc, relationDest);
    }
    else if(relationSrc && conceptDest) {
        return insertConnectorEdge(relationSrc, conceptDest);
    }
    return nullptr;
}

RelationNode* KnowledgeGraph::insertRelationNode(QString contentTextForm, qreal x, qreal y, qreal width, qreal height, QList<ConceptNode*> context, QList<ConceptNode*> answers) {
    RelationNode* node = insertCustomNode<RelationNode>();
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
    emit customElementInserted();
    return node;
}

void KnowledgeGraph::saveFile(std::ofstream& file) {
    boost::json::object jsonObject;
    boost::json::array jsonNodesArray;
    auto& nodes = get_nodes();
    for(qan::Node* node : nodes) {
        NodeBase* nodeBase = dynamic_cast<NodeBase*>(node);
        if(nodeBase) {
            jsonNodesArray.push_back(nodeBase->toJson());
        }
    }
    boost::json::array jsonEdgesArray;
    for(int i = 0; i < nodes.size(); i++) {
        for(int j = 0; j < nodes.size(); j++) {
            qan::Edge* edge = find_edge(nodes.getContainer()[i], nodes.getContainer()[j]);
            if(edge) {
                EdgeBase* edgeBase = dynamic_cast<EdgeBase*>(edge);
                if(edgeBase) {
                    jsonEdgesArray.push_back(edgeBase->toJson(i, j));
                }
            }
        }
    }
    jsonObject["nodes"] = jsonNodesArray;
    jsonObject["edges"] = jsonEdgesArray;
    file << boost::json::serialize(jsonObject);
    file.flush();
}

void KnowledgeGraph::loadFile(std::ifstream& file) {
    clear();
    boost::json::value jsonValue;
    file >> jsonValue;
    boost::json::object jsonObject = jsonValue.as_object();
    boost::json::array jsonNodesArray = jsonObject["nodes"].as_array();
    boost::json::string conceptNodeTypeName = ConceptNode().getTypeName();
    boost::json::string relationNodeTypeName = RelationNode().getTypeName();
    for(boost::json::value jsonNodeValue : jsonNodesArray) {
        boost::json::object jsonNode = jsonNodeValue.as_object();
        boost::json::string type = jsonNode["type"].as_string();
        NodeBase* node = nullptr;
        if(type == conceptNodeTypeName) {
            node = insertCustomNode<ConceptNode>();
        }
        else if(type == relationNodeTypeName) {
            node = insertCustomNode<RelationNode>();
        }
        if(node) {
            node->loadJson(jsonNode);
        }
    }
    boost::json::array jsonEdgesArray = jsonObject["edges"].as_array();
    boost::json::string questionEdgeTypeName = QuestionEdge().getTypeName();
    boost::json::string connectorEdgeTypeName = ConnectorEdge().getTypeName();
    for(boost::json::value jsonEdgeValue : jsonEdgesArray) {
        boost::json::object jsonEdge = jsonEdgeValue.as_object();
        boost::json::string type = jsonEdge["type"].as_string();
        int src = jsonEdge["src"].as_int64();
        int dest = jsonEdge["dest"].as_int64();
        NodeBase* srcNode = dynamic_cast<NodeBase*>(get_nodes().getContainer()[src]);
        NodeBase* destNode = dynamic_cast<NodeBase*>(get_nodes().getContainer()[dest]);
        EdgeBase* edge = nullptr;
        if(type == questionEdgeTypeName) {
            edge = insertCustomEdge<QuestionEdge>(srcNode, destNode);
        }
        else if(type == connectorEdgeTypeName) {
            edge = insertCustomEdge<ConnectorEdge>(srcNode, destNode);
        }
        if(edge) {
            edge->loadJson(jsonEdge);
        }
    }
}