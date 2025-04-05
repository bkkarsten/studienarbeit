#include "Question.hpp"

void Question::setContentTextForm(const QString &textForm) {
    bool changes = (textForm != getContentTextForm());
    content.setTextForm(textForm, getContentItem());
    if(changes) {
        changed();
    }
} 

boost::json::object Question::questionToJson() {
    boost::json::object json;
    json["customWeight"] = customWeight;
    json["flashcardMetadata"] = fcMetadata;
    json["lastAnswered"] = lastAnswered.toString().toStdString();
    json["lastChanged"] = lastChanged.toString().toStdString();
    json["content"] = getContentTextForm().toStdString();
    return json;
}

void Question::questionLoadJson(boost::json::object json) {
    customWeight = json["customWeight"].as_double();
    fcMetadata = json["flashcardMetadata"].as_object();
    lastAnswered = QDateTime::fromString(QString::fromStdString(std::string(json["lastAnswered"].as_string())), Qt::ISODate);
    lastChanged = QDateTime::fromString(QString::fromStdString(std::string(json["lastChanged"].as_string())), Qt::ISODate);
    setContentTextForm(QString::fromStdString(std::string(json["content"].as_string())));
}

void Question::setCustomWeight(float customWeight) {
    bool changes = customWeight != this->customWeight;
    this->customWeight = customWeight;
    if(changes) {
        emitWeightChangedSignal();
    }
}

void Question::changed() {
    lastChanged = QDateTime::currentDateTime();
    emitContentChangedSignal();
}