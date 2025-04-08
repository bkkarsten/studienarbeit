#ifndef FLASHCARDALGORITHM_H
#define FLASHCARDALGORITHM_H

#include <QString>
#include <QStringList>
#include "Question.hpp"

/**
 * @brief An interface for flashcard algorithms. They are responsible for deciding when
 * a question is due. Note that they do not directly select the questions to be reviewed.
 * It is recommended that the algorithms remain stateless.
 */
class FlashcardAlgorithm {
public:
    /**
     * @brief Should return the name of the algorithm.
     */
    virtual QString displayName() const = 0;
    /**
     * @brief Should return the number of answer quality levels.
     */
    virtual unsigned int numAnswerQualities() const = 0;
    /**
     * @brief Should return a list of the names of the answer quality levels, such as
     * incorrect, correct but hard, easy etc.
     */
    virtual QStringList answerQualityNames() const = 0;
    /**
     * @brief Returns the colours of the answer quality levels to be applied to the 
     * corresponding buttons in the GUI.
     */
    virtual QStringList answerQualityColours() const { return QStringList(); }
    /**
     * @brief Should set all unset values in the question's flashcard metadata to default values.
     * Other checks and logic which are necessary before the question is used by the algorithm 
     * can also be performed.
     */
    virtual void initialise(Question*) const = 0;
    /**
     * @brief Should apply default values to the question's flashcard metadata
     */
    virtual void reset(Question*) const = 0;
    /**
     * @brief Should return whether the question is due for review.
     */
    virtual bool due(Question*) const = 0;
    /**
     * @brief Should return a weight for a question that can be used in a graph algorithm.
     * More difficult questions should get lower weights such that they are more likely 
     * to be traversed (asked). For example, the number of days until review can be used.
     */
    virtual float weight(Question*) const = 0;
    /**
     * @brief Should modify the question's flashcard metadata based on the quality level of
     * the answer and return whether the question needs to be reviewed again in this
     * session if the review model supports it.
     */
    virtual bool answered(Question*, unsigned int quality) const = 0;
};


#endif