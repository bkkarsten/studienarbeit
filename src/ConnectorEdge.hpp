#ifndef CONNECTOREDGE_H
#define CONNECTOREDGE_H

#include "EdgeBase.hpp"

/**
 * @brief An edge in the graph that connects relation nodes to concept nodes.
 */
class ConnectorEdge : public EdgeBase {
public:
    ConnectorEdge(QObject* parent) : EdgeBase(parent) {}
    /**
     * @brief Whether the edge is valid. True if out of the source and destination nodes,
     * exactly one is a concept node and one is a relation node.
     */
    bool valid() override;
    /**
     * @brief Returns the relation node that is connected to this
     */
    Question* getQuestion() override;
};


#endif