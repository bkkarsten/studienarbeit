#ifndef CONNECTOREDGE_H
#define CONNECTOREDGE_H

#include "EdgeBase.hpp"

/**
 * @brief An edge in the graph that connects relation nodes to concept nodes.
 */
class ConnectorEdge : public EdgeBase {
private:
    boost::json::object propertiesToJson() override { return boost::json::object(); }
    void propertiesLoadJson(boost::json::object json) override {}
public:
    ConnectorEdge(QObject* parent = nullptr) : EdgeBase(parent) {}

    boost::json::string getTypeName() override { return "ConnectorEdge"; }
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