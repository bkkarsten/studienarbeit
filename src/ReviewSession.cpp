#include "ReviewSession.hpp"

ReviewSession::ReviewSession(std::unique_ptr<ReviewModel> model, const KnowledgeGraph& graph, QQuickItem* reviewViewItem)
    : reviewModel(std::move(model))
    , reviewView(reviewViewItem)
    , graph(graph)
{
    if(!reviewView) {
        qWarning() << "ReviewView is null!";
        return;
    }
    contextContents = reviewView->findChild<QQuickItem*>("contextContents");
    questionContent = reviewView->findChild<QQuickItem*>("questionContent");
    answerContents = reviewView->findChild<QQuickItem*>("answerContents");

    FlashcardAlgorithm* fcAlgo = reviewModel->getFlashcardAlgorithm();
    if(fcAlgo) {
        QQmlProperty::write(reviewView, "buttonTexts", fcAlgo->answerQualityNames());
        QQmlProperty::write(reviewView, "buttonColours", fcAlgo->answerQualityColours());
        QQmlProperty::write(reviewView, "numButtons", fcAlgo->numAnswerQualities());
    }
    else {
        qWarning() << "ReviewSession's ReviewModel does not have a flashcard algorithm!";
    }
}

void ReviewSession::showQuestion(AskedQuestion askedQuestion) {
    QQmlProperty::write(reviewView, "reversed", askedQuestion.direction);
    QQmlProperty::write(reviewView, "revealed", false);
    Question* q = askedQuestion.question;
    if(q == nullptr) {
        return;
    }
    QQmlProperty::write(reviewView, "numContexts", q->getContext().size());
    int i = 0;
    for(ConceptNode* context : q->getContext()) {
        QQuickItem* contentItem = nullptr;
        QMetaObject::invokeMethod(contextContents, "itemAt",
                                  Q_RETURN_ARG(QQuickItem*, contentItem),
                                  Q_ARG(int, i));
        if(contentItem != nullptr) {
            context->getContent().apply(contentItem);
        }
        i++;
    }
    QQmlProperty::write(reviewView, "numAnswers", q->getAnswers().size());
    i = 0;
    for(ConceptNode* answer : q->getAnswers()) {
        QQuickItem* contentItem = nullptr;
        QMetaObject::invokeMethod(answerContents, "itemAt",
                                  Q_RETURN_ARG(QQuickItem*, contentItem),
                                  Q_ARG(int, i));
        if(contentItem != nullptr) {
            answer->getContent().apply(contentItem);
        }
        i++;
    }
    if(questionContent != nullptr) {
        q->getContent().apply(questionContent);
    }
}

void ReviewSession::answerQuestion(unsigned int quality) {
    reviewModel->answerQuestion(quality);
    AskedQuestion next = reviewModel->nextQuestion();
    if(next.question == nullptr) {
        emit finished();
    }
    else {
        showQuestion(next);
    }
}

bool ReviewSession::start() {
    bool anyQuestions = reviewModel->initialise(graph);
    if(anyQuestions) {
        showQuestion(reviewModel->nextQuestion()); // display the first question
    }
    return anyQuestions;
}