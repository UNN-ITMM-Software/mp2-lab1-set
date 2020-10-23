#include "tratio.h"

TRatio::TRatio(int num, int den)
{
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