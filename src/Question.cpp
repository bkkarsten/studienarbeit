#include "Question.hpp"

boost::json::object Question::questionToJson() {
    boost::json::object json;
    json["proficiency"] = proficiency;
    json["customWeight"] = customWeight;
    json["lastAnswered"] = lastAnswered.toString().toStdString();
    json["lastCorrectlyAnswered"] = lastCorrectlyAnswered.toString().toStdString();
    json["lastChanged"] = lastChanged.toString().toStdString();
    json["content"] = content.getTextForm().toStdString();
    return json;
}