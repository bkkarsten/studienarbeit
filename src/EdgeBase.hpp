#ifndef EDGEBASE_H
#define EDGEBASE_H

#include <QuickQanava>

#include <boost/json.hpp>

class Question;

/**
 * @brief Base class for edges in the graph. 
 */
class EdgeBase : public qan::Edge {
private:
    /**
     * @brief Get the type name of the edge for json representation.
     */
    virtual boost::json::string getTypeName() = 0;
    /**
     * @brief Convert the edge to a JSON object, excluding the type name.
     */
    virtual boost::json::object propertiesToJson() = 0;
public:
    EdgeBase(QObject* parent) : qan::Edge(parent) {}
    /**
     * @brief Returns the question that is associated with this.
     */
    virtual Question* getQuestion() = 0;
    /**
     * @brief Whether the edge is valid. True if not overridden.
     */
    virtual bool valid() { return true; }

    /**
     * @brief Load the edge from a JSON object.
     */
    // virtual void loadJson(const boost::json::object& jsonObject) = 0;
    /**
     * @brief Save the node to a JSON object, including the type name.
     */
    virtual boost::json::object toJson(int srcId, int destId) {
        boost::json::object json = propertiesToJson();
        json["type"] = getTypeName();
        json["src"] = srcId;
        json["dest"] = destId;
        return json;
    }
};


#endif