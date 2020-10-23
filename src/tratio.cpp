#include "tratio.h"

TRatio::TRatio(int numerator, int denominator)
{
    if (denominator == 0)
        throw "Denominator can't be zero!";

    if (denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }

    numerator_ = numerator;
    denominator_ = denominator;
}

int TRatio::GetNumerator()
{
    return numerator_;
}

int TRatio::GetDenominator()
{
    return denominator_;
}
