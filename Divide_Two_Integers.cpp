class Solution {
public:
    int divide(int dividend, int divisor) {
        if(!divisor) return INT_MAX;
        if(divisor == 1) return dividend;
        if(divisor == -1){
            if(dividend == INT_MIN) {return INT_MAX;}
            else {return -dividend;}
        }

        bool s1 = dividend<0;
        bool s2 = divisor<0;

        unsigned int nom = s1?-dividend:dividend;
        unsigned int den = s2?-divisor:divisor;

        unsigned int rem = 0;
        unsigned int quot = 0;

        for(int i=31; i>=0;--i){
            rem <<= 1;
            rem |= (nom >> i) & 1;
            if(rem >= den){
                rem -= den;
                quot |= (1<<i);
            }
        }

        return s1^s2?-quot:quot;
    }
};