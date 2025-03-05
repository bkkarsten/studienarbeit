#ifndef NODEBASE_H
#define NODEBASE_H

#include <QuickQanava>

/**
 * @brief Base class for nodes in the graph.
 */
class NodeBase : public qan::Node {
protected:
    NodeBase(QObject* parent) : qan::Node(parent) {}
public:
    /**
     * @brief Whether the node is valid. True if not overridden.
     */
    virtual bool valid() { return true;}
};


#endif