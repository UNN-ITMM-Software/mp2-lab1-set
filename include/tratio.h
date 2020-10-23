#pragma once

class TRatio
{
 public:
    TRatio(int num=1, int den=1);
    int GetNumerator();
    int GetDenominator();

 private:
    int numerator_;
    int denominator_;
};
