		//Add Digits,Digital Root问题，解法1如下：
		int addDigits(int num) 
		{
			int result=num;
			while(result>9)
			{
				int temp =0;
				while(result)
				{
					temp+=result%10;
					result/=10;
				}
            result=temp;
			}
        return result;
		}
		//解法2：reference:http://my.oschina.net/Tsybius2014/blog/497645
		int addDigits_v2(int num) 
		{
			return (num - 1) % 9 + 1;
		}