#ifndef NODEBASE_H
#define NODEBASE_H

#include <QuickQanava>
#include <boost/json.hpp>

using boost::json::object;

/**
 * @brief Base class for nodes in the graph.
 */
class NodeBase : public qan::Node {
    Q_OBJECT
private:
    /**
     * @brief Convert the properties specific to the node implementation to a JSON object.
     */
    virtual boost::json::object propertiesToJson() = 0;
    /**
     * @brief Load the properties specific to the node implementation from a JSON object.
     */
    virtual void propertiesLoadJson(boost::json::object json) = 0;
protected:
    NodeBase(QObject* parent) : qan::Node(parent) {}
public:
    /**
     * @brief Whether the node is valid. True if not overridden.
     */
    virtual bool valid() { return true;}
    
    /**
     * @brief Get the type name of the node for json representation.
     */
    virtual boost::json::string getTypeName() = 0;

    /**
     * @brief Save the node to a JSON object.
     */
    virtual boost::json::object toJson();
    /**
     * @brief Load the node from a JSON object.
     */
    virtual void loadJson(boost::json::object json);
signals:
    void anythingChanged();
};


#endif