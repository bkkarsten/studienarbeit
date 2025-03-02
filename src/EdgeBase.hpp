#ifndef EDGEBASE_H
#define EDGEBASE_H

#include <QuickQanava>

class Question;

/**
 * @brief Base class for edges in the graph. 
 */
class EdgeBase : public qan::Edge {
public:
    /**
     * @brief Returns the question that is associated with this.
     */
    virtual Question* getQuestion() const = 0;
};


#endif