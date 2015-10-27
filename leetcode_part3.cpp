#include"header.h"
using namespace std;
namespace panzg_leetcode
{
	class Solution
	{
	public:
		/*Spiral Matrix*/
		vector<int> spiralOrder(vector<vector<int>>& matrix)
		{
			vector<int> result;
			if (matrix.empty())
				return result;
			int beginX = 0, endX = matrix[0].size() - 1;
			int beginY = 0, endY = matrix.size() - 1;
			while (true)
			{
				//��
				for (int j = beginX; j <= endX; ++j)
					result.push_back(matrix[beginY][j]);
				if (++beginY > endY)
					break;
				//��
				for (int i = beginY; i <= endY; ++i)
					result.push_back(matrix[i][endX]);
				if (beginX > --endX)
					break;
				//��
				for (int j = endX; j >= beginX; --j)
					result.push_back(matrix[endY][j]);
				if (--endY < beginY)
					break;
				//��
				for (int i = endY; i >= beginY; --i)
					result.push_back(matrix[i][beginX]);
				if (++beginX > endX)
					break;
			}
			return result;
		}
		/*Spiral Matrix 2*/
		vector<vector<int>> generateMatrix(int n)
		{
			vector<vector<int>> matrix(n, vector<int>(n));
			int begin = 0, end = n - 1;
			int num = 1;
			while (begin < end)
			{
				for (int i = begin; i < end; ++i)
					matrix[begin][i] = num++;
				for (int i = begin; i < end; ++i)
					matrix[i][end] = num++;
				for (int j = end; j > begin; --j)
					matrix[end][j] = num++;
				for (int i = end; i > begin; --i)
					matrix[i][begin] = num++;
				++begin;
				--end;
			}
			if (begin == end) matrix[begin][begin] = num;
			return matrix;
		}
		/*ZigZag Conversion ��ѧ����*/
		string convert(string s, int numRows)
		{
			if (numRows <= 1 || s.size() <= 1)
				return s;
			string result;
			for (int i = 0; i < numRows; i++) 
			{
				for (int j = 0, index = i; index < s.size();j++, index = (2 * numRows - 2) * j + i) 
				{
					result.append(1, s[index]); // ��ֱԪ��
					if (i == 0 || i == numRows - 1) 
						continue; // б�Խ�Ԫ��
					if (index + (numRows - i - 1) * 2 < s.size())
						result.append(1, s[index + (numRows - i - 1) * 2]);
				}
			}
			return result;
		}
		/*Divide Two Integers*/
		int divide(int dividend, int divisor)
		{
			if (!divisor) return INT_MAX;
			if (divisor == 1) return dividend;
			if (divisor == -1){
				if (dividend == INT_MIN) { return INT_MAX; }
				else { return -dividend; }
			}

			bool s1 = dividend < 0;
			bool s2 = divisor < 0;

			unsigned int nom = s1 ? -dividend : dividend;
			unsigned int den = s2 ? -divisor : divisor;

			unsigned int rem = 0;
			unsigned int quot = 0;

			for (int i = 31; i >= 0; --i){
				rem <<= 1;
				rem |= (nom >> i) & 1;
				if (rem >= den){
					rem -= den;
					quot |= (1 << i);
				}
			}

			return s1^s2 ? -quot : quot;
		}
		// LeetCode, Text Justification
		// ʱ�临�Ӷ� O(n)���ռ临�Ӷ� O(1)
		vector<string> fullJustify(vector<string> &words, int L) 
		{
			vector<string> result;
			const int n = words.size();
			int begin = 0, len = 0; // ��ǰ�е���㣬��ǰ����
			for (int i = 0; i < n; ++i) {
				if (len + words[i].size() + (i - begin) > L) 
				{
					result.push_back(connect(words, begin, i - 1, len, L, false));
					begin = i;
					len = 0;
				}
				len += words[i].size();
			}
			// ���һ�в��� L
			result.push_back(connect(words, begin, n - 1, len, L, true));
			return result;
		}
		/**
		* @brief �� words[begin, end] ����һ��
		* @param[in] words �����б�
		* @param[in] begin ��ʼ
		* @param[in] end ����
		* @param[in] len words[begin, end] ���е��ʼ������ĳ���
		* @param[in] L ��Ŀ�涨��һ�г���
		* @param[in] is_last �Ƿ������һ��
		* @return �����ĵ�ǰ��
		*/
		string connect(vector<string> &words, int begin, int end,int len, int L, bool is_last) 
		{
			string s;
			int n = end - begin + 1;
			for (int i = 0; i < n; ++i) 
			{
				s += words[begin + i];
				addSpaces(s, i, n - 1, L - len, is_last);
			}
			if (s.size() < L) s.append(L - s.size(), ' ');
			return s;
		}
		/**
		* @brief ��ӿո�.
		* @param[inout]s һ��
		* @param[in] i ��ǰ��϶�����
		* @param[in] n ��϶����
		* @param[in] L �ܹ���Ҫ��ӵĿն���
		* @param[in] is_last �Ƿ������һ��
		* @return ��
		*/
		void addSpaces(string &s, int i, int n, int L, bool is_last) 
		{
			if (n < 1 || i > n - 1) return;
			int spaces = is_last ? 1 : (L / n + (i < (L % n) ? 1 : 0));
			s.append(spaces, ' ');
		}
		//LeetCode, Max Points on a Line
		// ����ö�ٷ����Ա�Ϊ���ģ�ʱ�临�Ӷ� O(n^3)���ռ临�Ӷ� O(1)
		int maxPoints(vector<Point>& points)
		{
			if (points.size() < 3)
				return points.size();
			int result = 0;

			for (int i = 0; i < points.size()-1;i++)
			{
				for (int j = i + 1; j < points.size();j++)
				{
					int sign = 0;
					int a, b, c;
					if (points[i].x == points[j].x)
						sign = 1;
					else
					{
						a = points[j].x - points[i].x;
						b = points[j].y - points[i].y;
						c = a*points[i].y - b*points[i].x;
					}
					int count = 0;
					for (int k = 0; k < points.size();k++)
					{
						if ((0 == sign && a*points[k].y == c + b*points[k].x) ||
							(1 == sign && points[k].x == points[j].x))
							count++;
					}
					if (count > result)
						result = count;
				}
			}
			return result;
		}

	};
}
int main()
{
	panzg_leetcode::Solution sol;
	vector<vector<int>> vec(1, vector<int>(2, 3));
	auto res = sol.divide(-2147483648,-1);
	cout << res;
	system("pause");
}