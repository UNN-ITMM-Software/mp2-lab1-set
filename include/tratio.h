#pragma once

class TRatio
{
 public:
    TRatio(int numerator = 0, int denominator = 1);

    int GetNumerator();
    int GetDenominator();

 private:
    int numerator_;
    int denominator_;
};
