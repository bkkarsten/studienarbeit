#ifndef REVIEWMODEL_H
#define REVIEWMODEL_H

#include "Question.hpp"
#include "KnowledgeGraph.hpp"
#include "FlashcardAlgorithm.hpp"

/**
 * @brief Interface for how questions will be selected from the knowledge graph
 */
class ReviewModel {

public:

    /**
     * @brief Initialise the review model. For example, collect the due questions and decide the order.
     * @param graph The knowledge graph to take the questions from
     * @param algorithm The flashacrd algorithm that decides when a question is due
     */
    virtual void initialise(const KnowledgeGraph& graph, const FlashcardAlgorithm& algorithm) = 0;
    /**
     * @brief Get the next question to be asked.
     */
    virtual Question* nextQuestion() = 0;
    /**
     * @brief Give an answer to the current question. This should call the algorithm's answered function.
     */
    virtual void answerQuestion(unsigned int quality) = 0;

};



#endif