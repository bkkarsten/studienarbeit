#ifndef REVIEWMODEL_H
#define REVIEWMODEL_H

#include "AskedQuestion.hpp"
#include "KnowledgeGraph.hpp"
#include "FlashcardAlgorithm.hpp"

#include <memory>

/**
 * @brief Interface for how questions will be selected from the knowledge graph
 */
class ReviewModel {

protected:

    std::unique_ptr<FlashcardAlgorithm> fcAlgo;

    ReviewModel(std::unique_ptr<FlashcardAlgorithm> algorithm)
        : fcAlgo(std::move(algorithm)) {}
    ReviewModel() = delete;

public:

    FlashcardAlgorithm* getFlashcardAlgorithm() const { return fcAlgo.get(); }

    /**
     * @brief Initialise the review model. For example, collect the due questions and decide the order.
     * @param graph The knowledge graph to take the questions from
     * @return Whether there is anything to review.
     */
    virtual bool initialise(const KnowledgeGraph& graph) = 0;
    /**
     * @brief Get the next question to be asked.
     */
    virtual AskedQuestion nextQuestion() = 0;
    /**
     * @brief Give an answer to the current question. This should call the algorithm's answered function.
     */
    virtual void answerQuestion(unsigned int quality) = 0;
    /**
     * @brief Returns the number of questions in the review model.
     */
    virtual int numQuestions() = 0;

};



#endif