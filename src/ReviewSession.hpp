#ifndef REVIEWSESSION_H
#define REVIEWSESSION_H

#include <QQuickItem>

#include "AskedQuestion.hpp"
#include "FlashcardAlgorithm.hpp"
#include "ReviewModel.hpp"

/**
 * @brief This class acts as a mediator between the review model and the GUI. It applies the review model's
 * logic to the GUI and calls its functions based on user input.
 */
class ReviewSession : public QObject {
    Q_OBJECT

private:

    QQuickItem* reviewView;
    QQuickItem* contextContents; // Repeater
    QQuickItem* questionContent; // Content
    QQuickItem* answerContents;  // Repeater

    std::unique_ptr<ReviewModel> reviewModel;

    const KnowledgeGraph& graph;

    /**
     * @brief Shows the question
     */
    void showQuestion(AskedQuestion);

public:

    ReviewSession(std::unique_ptr<ReviewModel> reviewModel, const KnowledgeGraph& graph, QQuickItem* reviewViewItem);

    /**
     * @brief Initialises the review model and displays the first question
     */
    bool start();

    /**
     * @brief Passes the quality of the answer to the review model and displays the nest question.
     */
    void answerQuestion(unsigned int quality);

signals:
    void finished();

};


#endif