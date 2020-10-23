#include "tratio.h"

TRatio::TRatio(int num, int den)
{
    if (den == 0)
        throw "Denominator can't be zero!";

    numerator_ = num;
    denominator_ = den;
}

int TRatio::GetNumerator()
{
    return numerator_;
}

int TRatio::GetDenominator()
{
    return denominator_;
}