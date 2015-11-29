class Solution {
public:
		/*Count Primes*/
        int countPrimes(int n) 
		{
			if (n <= 2)
				return 0;

			bool *prime = new bool[n];
			int i, j, k;

			for (i = 0; i < n; i++)
				prime[i] = true;

			for (i = 2; i < n; i++)
			{
				if (prime[i] == true)
				{
					for (j = i; j + i < n; j += i)
						prime[j + i] = false;
				}
			}
			for (i = 2, k = 0; i < n; i++)
			{
				if (prime[i])
					k++;
			}
			return k;
		}
};