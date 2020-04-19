#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <climits>
#include <sys/time.h>
#include "zg_tool.hpp"
using namespace std;

vector<int> vDayNineCnt(10000*12*31+1,0);

int solveReplace(vector<int>& vData)
{
    while(1) //这个循环一定能return的
    {
        //找出最大数
        int idxL = 0;
        int iMaxVal = INT_MIN;
        for (size_t i = 0; i < vData.size(); i++)
        {
            if(vData[i] > iMaxVal)
            {
                idxL = i;
                iMaxVal = vData[i];
            }
        }
        
        //找出最小数
        int idxS = 0;
        int iMinVal = INT_MAX;
        for (size_t i = 0; i < vData.size(); i++)
        {
            if(vData[i] < iMinVal)
            {
                idxS = i;
                iMinVal = vData[i];
            }
        }

        if(iMinVal == iMaxVal) return iMaxVal;

        //替换
        vData[idxL] = vData[idxS] = (iMaxVal - iMinVal);
    }
    return 0;
}

//简单数字游戏
long long solveNumGanme(vector<int>& vData, int m)
{
    //top k 先排序
    std::nth_element(vData.begin(), vData.begin() + 2*m, vData.end());
    std::sort(vData.begin(), vData.begin() + 2*m);

    //计算乘积之和
    long long iSum = 0;
    for (size_t i = 0; i < m; i++)
    {
        iSum += vData[i] * vData[2*m -1 - i];
    }
    return iSum;
}


bool bSpecialYear(int year)
{
    if(year%4 == 0 && year%100 != 0)
        return true;
    if(year%400 == 0)
        return true;
    return false;
}

int countDayNine(int year, int month, int day)
{
    //cout << year << "\t" << month << "\t" << day << endl;
    int iNineCnt = 0;
    while(year)
    {
        if(year%10 == 9) ++iNineCnt;
        year /= 10;
    }
    if(month == 9) ++iNineCnt;
    if(day == 9 || day == 19 || day == 29) ++iNineCnt;
    return iNineCnt;
}

//多少个99999
int solvelHowManyNine(int leftyear, int leftmonth, int leftday, int rightyear, int rightmonth, int rightday)
{
    //cout << leftyear << "\t" << leftmonth << "\t" << leftday << "\t" << rightyear << "\t" << rightmonth << "\t" << rightday << endl;

    vector<int> normalYear = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    vector<int> specialYear = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    int iNineCnt = 0;
     bool isSpecialYear = bSpecialYear(leftyear);
    //算下中间年份的整年的数据
    for (size_t i = leftyear; i <= rightyear; i++)
    {
        isSpecialYear = bSpecialYear(i);
        int j  = (i == leftyear ? leftmonth : 1);
        int j_max = (i == rightyear ? rightmonth : 12);
        for (; j <= j_max; j++)
        {
            int k = ( i == leftyear && j== leftmonth) ? leftday : 1;
            int k_max = (i == rightyear && j == rightmonth) ? rightday : (isSpecialYear ? specialYear[j] : normalYear[j]);
            for(; k <= k_max; k++)
            {
                int key = i*12*31 + j*31 + k;
                iNineCnt += vDayNineCnt[key];
                //cout << "year=" << i << ",month=" << j << ",day=" << k <<  ",key=" << key <<  ",cnt=" << vDayNineCnt[key] << endl;
            }
        }
        
    }
    return iNineCnt;
}

int main()
{

    #if 0
    //计算9的个数--先打表
     //先缓存一个时间戳吧
    struct  timeval start;
    struct  timeval end;
    //记录两个时间差
    unsigned  long diff;
 
    //第一次获取时间，即表示开始记时
    gettimeofday(&start,NULL);
    #endif

    for (size_t i = 2000; i <= 9999; i++)
    {
        for (size_t j = 1; j <= 12; j++)
        {
            for(size_t k = 1; k<= 31; k++)
            {
                int key = i*12*31 + j*31 + k;
                vDayNineCnt[key] = countDayNine(i,j,k);//= ;
            }
        }
    }

    #if 0
    cout << vDayNineCnt.size() << endl;
    //第二次获取时间，即表示结束记时
    gettimeofday(&end,NULL);
    //计算时间差，并打印
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    cout << "cost time="<< diff << endl;
    #endif

    int iCaseNum = 0;
    cin >> iCaseNum;
    while (iCaseNum-- > 0)
    {
        int leftyear,leftmonth, leftday, rightyear, rightmonth, rightday;
        cin >> leftyear >> leftmonth >> leftday >> rightyear >> rightmonth >> rightday;
        cout << solvelHowManyNine(leftyear, leftmonth, leftday, rightyear, rightmonth, rightday) << endl;
    }
}