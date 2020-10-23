#pragma once

class TRatio
{
 public:
    TRatio(int num=0, int den=0);
    int GetNumerator();
    int GetDenominator();

 private:
    int numerator_;
    int denominator_;
};
