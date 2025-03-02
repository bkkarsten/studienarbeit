#ifndef EDGEBASE_H
#define EDGEBASE_H

#include <QuickQanava>

class Question;

/**
 * @brief Base class for edges in the graph. 
 */
class EdgeBase : public qan::Edge {
public:
    EdgeBase(QObject* parent) : qan::Edge(parent) {}
    /**
     * @brief Returns the question that is associated with this.
     */
    virtual Question* getQuestion() = 0;
};


#endif