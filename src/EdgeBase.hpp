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
     * @brief Convert the properties specific to the edge implementation to a JSON object.
     */
    virtual boost::json::object propertiesToJson() = 0;
    /**
     * @brief Load the properties specific to the edge implementation from a JSON object.
     */ 
    virtual void propertiesLoadJson(boost::json::object json) = 0;
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
     * @brief Get the type name of the edge for json representation.
     */
    virtual boost::json::string getTypeName() = 0;

    /**
     * @brief Save the node to a JSON object.
     */
    virtual boost::json::object toJson(int srcId, int destId);
    /**
     * @brief Load the node from a JSON object.
     */
    virtual void loadJson(boost::json::object json);
};


#endif