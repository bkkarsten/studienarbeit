#ifndef QUESTION_H
#define QUESTION_H

#include <QDateTime>
#include <QQuickItem>

#include <Content.hpp>

class ConceptNode;

class Question {
private:
    float proficiency;
    float customWeight;
    QDateTime lastAnswered;
    QDateTime lastCorrectlyAnswered;
    QDateTime lastChanged;

    virtual QQuickItem* getContentItem() = 0; 

CONTENTOWNER(content, getContentItem);

public:
    Question();
    const QDateTime& getLastAnswered() const { return lastAnswered; }
    const QDateTime& getLastCorrectlyAnswered() const { return lastCorrectlyAnswered; }
    const QDateTime& getLastChanged() const { return lastChanged; }
    float getProficiency() const { return proficiency; }
    float getCustomWeight() const { return customWeight; }
    void setCustomWeight(float customWeight) { this->customWeight = customWeight; }
    
    void answered() { lastAnswered = QDateTime::currentDateTime(); }
    void correctlyAnswered() { lastCorrectlyAnswered = QDateTime::currentDateTime(); }
    void changed() { lastChanged = QDateTime::currentDateTime(); }
    /**
     * @brief Displays the question. TODO!
     */
    void* show(void*) { return nullptr; }
    /**
     * @brief Returns the Concept Nodes that specify the context of the question.
     */
    virtual QList<ConceptNode*> getContext() = 0;
    /**
     * @brief Returns the Concept Nodes that are the answers to the question.
     */
    virtual QList<ConceptNode*> getAnswers() = 0;
};


#endif 