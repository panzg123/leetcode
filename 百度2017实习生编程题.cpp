#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <numeric>
#include <utility>
#include <iomanip>

using namespace std;

void FIFO()
{
	int n, m;
	while (cin >> n >> m)
	{
		vector<int> page_queue;
		int temp;
		int count = 0;
		for (int i = 0; i < m;i++)
		{
			cin >> temp;
			auto pos = find(page_queue.begin(), page_queue.end(), temp);
			if (pos == page_queue.end())
			{
				count++;
				if (page_queue.size()>=n)
					page_queue.erase(page_queue.begin());
				page_queue.push_back(temp);
			}
		}
		cout << count << endl;
	}
}

void sjf()
{
	int n;
	while (cin >> n){
		vector<int> rts;
		vector<int> cts;
		for (int i = 0; i < n; i++){
			int r, t;
			cin >> r >> t;
			rts.push_back(r);
			cts.push_back(t);
		}

		int cur_time = 1;
		double wait_time = 0;

		while (!rts.empty()){
			// 确定要执行进程
			int cur_process = 0;
			for (int i = 0; i < rts.size(); i++) {
				if (rts[i] < rts[cur_process] || (rts[i] == rts[cur_process] && cts[i] < cts[cur_process])) // 对应两个优先级
					cur_process = i;
			}
			if (cur_time > rts[cur_process]){
				wait_time = wait_time + (cur_time - rts[cur_process]);
				cur_time = cur_time + cts[cur_process];
			}
			else{
				cur_time = rts[cur_process] + cts[cur_process];
			}
			rts.erase(rts.begin() + cur_process);
			cts.erase(cts.begin() + cur_process);
		}
		cout << setiosflags(ios::fixed) << setprecision(4) << wait_time / (float)n << endl;
	}
}

#if 0
int main()
{
	sjf();
	return 0;
}
#endif