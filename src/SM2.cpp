#include "SM2.hpp"

#include <QDate>
#include <algorithm>

QStringList SM2::answerQualityNames() const {
    return {
        "Complete blackout",
        "Incorrect but remembered",
        "Incorrect but seems easy",
        "Correct but very difficult",
        "Correct with hesitation",
        "Perfect answer"
    };
}

QStringList SM2::answerQualityColours() const {
    return {
        "black",
        "#d7090f",
        "#e28221",
        "#b3cd30",
        "#38c42e",
        "#00d4ff"
    };
}

void SM2::reset(Question* question) const {
    boost::json::object& meta = question->getFlashcardMetadata();
    meta["sm2_n"] = 0;
    meta["sm2_interval"] = 0;
    meta["sm2_easiness"] = 2.5;
    meta["sm2_duedate"] = QDate::currentDate().toString().toStdString();
}

void SM2::initialise(Question* question) const {
    boost::json::object& meta = question->getFlashcardMetadata();
    if(!meta.contains("sm2_n")) {
        meta["sm2_n"] = 0;
    }
    if(!meta.contains("sm2_interval")) {
        meta["sm2_interval"] = 0;
    }
    if(!meta.contains("sm2_duedate")) {
        meta["sm2_duedate"] = QDate::currentDate().toString().toStdString();
    }
    if(!meta.contains("sm2_easiness")) {
        meta["sm2_easiness"] = ef_default;
    }
}

bool SM2::due(Question* question) const {
    initialise(question);
    boost::json::object& meta = question->getFlashcardMetadata();
    QDate duedate = QDate::fromString(QString::fromStdString(std::string(meta["sm2_duedate"].as_string())));
    if(!duedate.isValid()) {
        qWarning() << "Invalid duedate encountered in SM2 algorithm!";
        return false;
    }
    return duedate <= QDate::currentDate();
}

float SM2::weight(Question* question) const {
    initialise(question);
    boost::json::object& meta = question->getFlashcardMetadata();
    QDate duedate = QDate::fromString(QString::fromStdString(std::string(meta["sm2_duedate"].as_string())));
    if(!duedate.isValid()) {
        qWarning() << "Invalid duedate encountered in SM2 algorithm!";
        return false;
    }
    int daysLeft = QDate::currentDate().daysTo(duedate);
    if(daysLeft < 0) {
        return 0.0f;
    }
    else return float(daysLeft);
}

bool SM2::answered(Question* question, unsigned int quality) const {
    if(quality > 5) {
        throw std::invalid_argument("Quality level given to SM-2 must be between 0 and 5.");
    }
    initialise(question);
    boost::json::object& meta = question->getFlashcardMetadata();
    int64_t& n = meta["sm2_n"].as_int64();
    double& easiness = meta["sm2_easiness"].as_double();
    int64_t& interval = meta["sm2_interval"].as_int64();
    if(quality < 3) {
        n = 0;
        interval = 0;
    }
    else if(quality >= 4) {    
        n++;
        easiness = std::clamp(easiness + (w0 + w1 * quality + w2 * quality * quality), 
            ef_min, ef_max);
        interval = int64_t(std::ceil((
            n == 1 ? i1 : (
            n == 2 ? i2 :
            interval * easiness
        )) / question->getCustomWeight()));
        QDate newDuedate = QDate::currentDate().addDays(interval);
        meta["sm2_duedate"] = newDuedate.toString().toStdString();
    }
    return quality < 4; // review again if answer quality below four
}