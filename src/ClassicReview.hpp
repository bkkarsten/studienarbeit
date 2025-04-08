#ifndef CLASSICREVIEW_H
#define CLASSICREVIEW_H

#include <QList>

#include "ReviewModel.hpp"

/**
 * @brief the classic review model, where all due questions are asked in random order.
 */
class ClassicReview : public ReviewModel {

private:

    Question* currentQuestion;
    QList<Question*> openQuestions;
    QList<Question*> againQuestions;

public:

    ClassicReview(const FlashcardAlgorithm& algorithm) : ReviewModel(algorithm) {}

    bool initialise(const KnowledgeGraph&) override;
    Question* nextQuestion() override;
    void answerQuestion(unsigned int) override;

};


#endif