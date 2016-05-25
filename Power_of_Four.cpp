//https://leetcode.com/problems/power-of-four/, 与isPowerOfThree思路一样
bool isPowerOfFour(int num)
{
    if (num < 0)
        return false;
    const double ratio = 1/log10(4);
    double diff = log10(num)*ratio;
    return abs(diff - round(diff)) < 1e-13;
}