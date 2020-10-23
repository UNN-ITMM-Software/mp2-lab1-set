#include "tratio.h"

TRatio::TRatio(int numerator, int denominator)
{
    if (denominator == 0)
        throw "Denominator can't be zero!";

    int divisor = gcd(numerator, denominator);
    numerator_ = numerator / divisor;
    denominator_ = denominator / divisor;

    if (denominator_ < 0)
    {
        numerator_ *= -1;
        denominator_ *= -1;
    }
}

int TRatio::GetNumerator()
{
    return numerator_;
}

int TRatio::GetDenominator()
{
    return denominator_;
}

int gcd(int a, int b)
{
    while(b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}