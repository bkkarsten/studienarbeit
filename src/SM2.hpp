#ifndef SUPERMEMO2_H
#define SUPERMEMO2_H

#include "FlashcardAlgorithm.hpp"

/**
 * @brief An implementation of the SuperMemo 2 algorithm. 
 * @copyright 
 * Algorithm SM-2, (C) Copyright SuperMemo World, 1991.
 * https://www.supermemo.com
 * https://www.supermemo.eu
 */
class SM2 : public FlashcardAlgorithm {

private:
// weights for calculating the new easiness factor
    static constexpr double w0 = -0.8;
    static constexpr double w1 = 0.28;
    static constexpr double w2 = -0.02;
// interval sizes for new items
    static constexpr uint64_t i1 = 1U;
    static constexpr uint64_t i2 = 6U;
// interval for easiness factor
    static constexpr double ef_min = 1.3;
    static constexpr double ef_max = 2.5;
    static constexpr double ef_default = 2.5;

public:

    QString displayName() override { return "SM-2"; }

    unsigned int numAnswerQualities() override { return 6; }

    QStringList answerQualityNames() override;

    QStringList answerQualityColours() override;

    void initialise(Question*) override;

    void reset(Question*) override;

    bool due(Question*) override;

    float weight(Question*) override;

    virtual bool answered(Question*, unsigned int) override;
};



#endif