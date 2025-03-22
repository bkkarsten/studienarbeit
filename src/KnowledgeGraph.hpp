#ifndef KNOWLEDGEGRAPH_H
#define KNOWLEDGEGRAPH_H

#include <QuickQanava>

#include "ConceptNode.hpp"
#include "QuestionEdge.hpp"
#include "RelationNode.hpp"
#include "ConnectorEdge.hpp"


template <typename T>
concept HasContentChangedSignal = requires(T t) {
    { t.contentChanged() }; 
};


class KnowledgeGraph : public qan::Graph {
    Q_OBJECT
    QML_ELEMENT

private:
    /**
     * @brief Inserts a node of a given type and if available, connects its contentChanged signal to the unsaved changes tracking.
     */
    template<typename NodeType>
    requires HasContentChangedSignal<NodeType>
    NodeType* insertCustomNode();
    template<typename NodeType>
    requires (!HasContentChangedSignal<NodeType>)
    NodeType* insertCustomNode();
    /**
     * @brief Inserts an edge of a given type and if available, connects its contentChanged signal to the unsaved changes tracking.
     */
    template<typename EdgeType>
    requires HasContentChangedSignal<EdgeType>
    EdgeType* insertCustomEdge(qan::Node* src, qan::Node* dest);
    template<typename EdgeType>
    requires (!HasContentChangedSignal<EdgeType>)
    EdgeType* insertCustomEdge(qan::Node* src, qan::Node* dest);

public:
    KnowledgeGraph(QQuickItem* parent = nullptr) : qan::Graph(parent) {}
    /**
     * @brief Checks whether all nodes and edges are valid.
     */
    bool valid();

    /**
     * @brief Saves the graph to a file in json format.
     */
    void saveFile(std::ofstream& file);
    /**
     * @brief Clears the graph and loads a graph from a file in json format.
     */
    void loadFile(std::ifstream& file);

    /**
     * @brief Inserts a ConceptNode into the graph and returns a pointer to it.
     * @param contentTextForm The content of the node represented by text.
     * @param x The x coordinate of the node.
     * @param y The y coordinate of the node
     * @param width The width of the node. If not specified, the default width is used.
     * @param height The height of the node. If not specified, the default height is used.
     */
    Q_INVOKABLE ConceptNode* insertConceptNode(QString contentTextForm = "",
                                   qreal x = 0,
                                   qreal y = 0,
                                   qreal width = -1,
                                   qreal height = -1);
    /**
     * @brief Inserts a QuestionEdge into the graph and returns a pointer to it.
     * @param src The source node of the edge.
     * @param dest The destination node of the edge.
     */
    Q_INVOKABLE QuestionEdge* insertQuestionEdge(ConceptNode* src, ConceptNode* dest, QString contentTextForm = "");
    /**
     * @brief Inserts a ConnectorEdge into the graph and returns a pointer to it.
     * @param src The source concept node of the edge.
     * @param dest The destination relation node of the edge.
     */
    Q_INVOKABLE ConnectorEdge* insertConnectorEdge(ConceptNode* src, RelationNode* dest);
    /**
     * @brief Inserts a ConnectorEdge into the graph and returns a pointer to it.
     * @param src The source relation node of the edge.
     * @param dest The destination concept node of the edge.
     */
    Q_INVOKABLE ConnectorEdge* insertConnectorEdge(RelationNode* src, ConceptNode* dest);
    /**
     * @brief Inserts the correct node type based on the type of src and dest, only if there is no such edge yet. 
     * QuestionEdge is inserted between two ConceptNodes; ConnectorEdge is inserted between ConceptNode and RelationNode.
     * Otherwise, no edge is inserted.
     * @param src The source node of the edge.
     * @param dest The destination node of the edge.
     */
    Q_INVOKABLE EdgeBase* insertCorrectEdge(NodeBase* src, NodeBase* dest);
    /**
     * @brief Inserts a RelationNode into the graph and returns a pointer to it.
     * @param contentTextForm The content of the node represented by text.
     * @param x The x coordinate of the node.
     * @param y The y coordinate of the node.
     * @param width The width of the node. If not specified, the default width is used.
     * @param height The height of the node. If not specified, the default height is used.
     * @param context The concept nodes from which a connector edge will point into the relation node.
     * @param answers The concept nodes to which a connector edge will point from the relation node.
     */
    Q_INVOKABLE RelationNode* insertRelationNode(QString contentTextForm = "",
                                     qreal x = 0,
                                     qreal y = 0,
                                     qreal width = -1,
                                     qreal height = -1,
                                     QList<ConceptNode*> context = QList<ConceptNode*>(),
                                     QList<ConceptNode*> answers = QList<ConceptNode*>());

signals:
    void customElementInserted();
    void contentEdited();

};

QML_DECLARE_TYPE(KnowledgeGraph)

#endif