#ifndef ASKEDQUESTION_H
#define ASKEDQUESTION_H

#include "Question.hpp"

enum Direction {
    FORWARD,
    BACKWARD
};

/**
 * @brief Includes a question and the direction in which it is asked
 */
struct AskedQuestion {
    Question* question;
    Direction direction;
};

constexpr AskedQuestion NO_QUESTION = {nullptr, Direction::FORWARD};


#endif