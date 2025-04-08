#include "ClassicReview.hpp"

#include <cstdlib>

bool ClassicReview::initialise(const KnowledgeGraph& graph) {
    openQuestions = graph.allQuestions().values();
    openQuestions.removeIf([&](Question* q) {
        return !fcAlgo.due(q);
    });
    return !openQuestions.isEmpty();
}

Question* ClassicReview::nextQuestion() {
    if(openQuestions.isEmpty()) {
        if(againQuestions.isEmpty()) {
            return nullptr;
        }
        openQuestions = againQuestions;
        againQuestions.clear();
    }
    int randomIndex = rand() % openQuestions.size();
    Question* next = openQuestions.takeAt(randomIndex);
    currentQuestion = next;
    return next;
}

void ClassicReview::answerQuestion(unsigned int quality) {
    if(currentQuestion == nullptr) {
        return;
    }
    bool again = fcAlgo.answered(currentQuestion, quality);
    if(again) {
        againQuestions.append(currentQuestion);
    }
    currentQuestion = nullptr;
}