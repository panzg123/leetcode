//用log来计算
bool isPowerOfThree(int n)
{
	if(n<=0)
		return false;
	const double ratio = 1/log2(3);
	double diff = log2(n)*ratio;
	//如果是3的幂，则diff应该为整数
	return abs(diff-round(diff))<1e-13;
}
//循环除
bool isPowerOfThree_v2(int n) 
{
    if(n>1)
        while(n%3==0) n /= 3;
    return n==1;
}