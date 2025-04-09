#include "ClassicReview.hpp"

#include <cstdlib>

ClassicReview::ClassicReview(std::unique_ptr<FlashcardAlgorithm> algorithm, bool bidirectional) 
    : ReviewModel(std::move(algorithm)) 
    , bidirectional(bidirectional)
{}

bool ClassicReview::initialise(const KnowledgeGraph& graph) {
    QSet<Question*> allQuestions = graph.allQuestions();
    for(Question* question : allQuestions) {
        if(fcAlgo->due(question)) {
            openQuestions.append({question, Direction(
                bidirectional ? rand() % 2 : Direction::FORWARD
            )});
        }
    }
    return !openQuestions.isEmpty();
}

AskedQuestion ClassicReview::nextQuestion() {
    if(openQuestions.isEmpty()) {
        if(againQuestions.isEmpty()) {
            return NO_QUESTION;
        }
        openQuestions = againQuestions;
        againQuestions.clear();
    }
    int randomIndex = rand() % openQuestions.size();
    AskedQuestion next = openQuestions.takeAt(randomIndex);
    currentQuestion = next;
    return next;
}

void ClassicReview::answerQuestion(unsigned int quality) {
    if(currentQuestion.question == nullptr) {
        return;
    }
    bool again = fcAlgo->answered(currentQuestion.question, quality);
    if(again) {
        againQuestions.append(currentQuestion);
    }
    currentQuestion = NO_QUESTION;
}