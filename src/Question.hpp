#ifndef QUESTION_H
#define QUESTION_H

#include <QDateTime>
#include <QQuickItem>

#include <boost/json.hpp>

#include "Content.hpp"

class ConceptNode;

/**
 * @brief An interface for questions.
 */
class Question {
private:
    float customWeight = 1.0;
    boost::json::object fcMetadata;
    QDateTime lastAnswered;
    QDateTime lastChanged;

    Content content; 
    virtual QQuickItem* getContentItem() = 0; 
    virtual void emitContentChangedSignal() = 0;
    virtual void emitWeightChangedSignal() = 0;
public: 
    const QString& getContentTextForm() const { return content.getTextForm(); }
    void setContentTextForm(const QString& textForm);

protected:
    boost::json::object questionToJson();
    void questionLoadJson(boost::json::object json);
public:
    Question() {};
    const QDateTime& getLastAnswered() const { return lastAnswered; }
    const QDateTime& getLastChanged() const { return lastChanged; }
    float getCustomWeight() const { return customWeight; }
    void setCustomWeight(float customWeight);
    boost::json::object& getFlashcardMetadata() { return fcMetadata; }
    
    void answered() { lastAnswered = QDateTime::currentDateTime(); }
    void changed();
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