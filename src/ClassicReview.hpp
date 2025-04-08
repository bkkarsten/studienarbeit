#ifndef CLASSICREVIEW_H
#define CLASSICREVIEW_H

#include <QList>

#include "ReviewModel.hpp"

/**
 * @brief the classic review model, where all due questions are asked in random order.
 */
class ClassicReview : public ReviewModel {

private:

    bool bidirectional;
    AskedQuestion currentQuestion;
    QList<AskedQuestion> openQuestions;
    QList<AskedQuestion> againQuestions;

public:

    /**
     * @param algorithm The algorithm that decides which questions are due
     * @param bidirectional Whether the questions should be asked in both directions
     */
    ClassicReview(const FlashcardAlgorithm& algorithm, bool bidirectional=false);

    bool initialise(const KnowledgeGraph&) override;
    AskedQuestion nextQuestion() override;
    void answerQuestion(unsigned int) override;

};


#endif