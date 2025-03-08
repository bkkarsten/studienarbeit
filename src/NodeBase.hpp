#ifndef NODEBASE_H
#define NODEBASE_H

#include <QuickQanava>
#include <boost/json.hpp>

using boost::json::object;

/**
 * @brief Base class for nodes in the graph.
 */
class NodeBase : public qan::Node {
private:
    /**
     * @brief Get the type name of the node for json representation.
     */
    virtual boost::json::string getTypeName() = 0;
    /**
     * @brief Convert the node to a JSON object, excluding the type name.
     */
    virtual boost::json::object propertiesToJson() = 0;
protected:
    NodeBase(QObject* parent) : qan::Node(parent) {}
public:
    /**
     * @brief Whether the node is valid. True if not overridden.
     */
    virtual bool valid() { return true;}
    /**
     * @brief Load the node from a JSON object.
     */
    // virtual void loadJson(const boost::json::object& jsonObject) = 0;
    /**
     * @brief Save the node to a JSON object, including the type name.
     */
    virtual boost::json::object toJson() {
        boost::json::object json = propertiesToJson();
        json["type"] = getTypeName();
        qan::NodeItem* item = getItem();
        json["x"] = item ? item->x() : 0;
        json["y"] = item ? item->y() : 0;
        json["width"] = item ? item->width() : -1;
        json["height"] = item ? item->height() : -1;
        return json;
    }
};


#endif