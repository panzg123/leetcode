#include"header.h"
using namespace std;
namespace nowcoder{
	class Solution{
	public:
		void Print(){
			cout << "hello nowcoder" << endl;
		}
		//华为机试，分割字符串
		void wordSplit()
		{
			string str;
			while (cin >> str)
			{
				if (str.length() <= 8)
				{
					str += string(8 - str.length(), '0');
					cout << str<<endl;
				}
				else
				{
					int index = 0;
					while (index+7 < str.length())
					{
						string str_temp(str, index, 8);
						cout << str_temp << endl;
						index += 8;
					}
					if (index < str.length())
					{
						string str_temp(str, index, str.length() - index);
						str_temp += string(8 + index - str.length(), '0');
						cout << str_temp << endl;
					}
				}
			}
		}
		//华为机试，进制转换
		void convertHex2Dec()
		{
			string str;
			while (cin>>str)
			{
				stringstream ss(str);
				string hex_str;
				while (ss >> hex_str)
				{
					//十六进制转换为10进制
					int dec_number = stoi(hex_str, nullptr, 16);
					cout << dec_number << " ";
				}
				cout << endl;
			}
		}
		//华为机试，合并序列
		void merge_array(){
			int number;
			while (cin >> number)
			{
				unordered_map<int, int> map;
				int key, value;
				for (int i = 0; i < number; i++){
					cin >> key >> value;
					map[key] += value;
				}
				for (auto item : map){
					cout << item.first << " " << item.second << endl;
				}
			}
		}
		void charcount()
		{
			string str;
			vector<int> flag(128, 0);
			getline(cin, str);
			int ret_count = 0;
			for (int i = 0; i < str.length(); i++){
				if (str[i] < 128 && flag[str[i]] == 0){
					ret_count++;
					flag[str[i]] = 1;
				}
			}
			cout << ret_count << endl;
		}
		void check1number()
		{
			int number;
			cin >> number;
			int ret = 0;
			while (number){
				ret++;
				number = number&(number - 1);
			}
			cout << ret << endl;
		}
		//华为机试，判断是否是合格的密码
		bool isValidPasswd(string str)
		{
			if (str.length() <= 8)
				return false;
			vector<int> flag(4, 0);
			int count = 0;
			for (int i = 0; i < str.length();i++)
			{
				if (isupper(str[i]) && flag[0] == 0)
				{
					count++;
					flag[0] = 1;
				}
				else if (islower(str[i]) && flag[1]==0)
				{
					count++;
					flag[1] = 1;
				}
				else if (isdigit(str[i]) && flag[2] == 0)
				{
					count++;
					flag[2] = 1;
				}
				else if (!(isdigit(str[i])||islower(str[i])||isupper(str[i]))&&flag[3]==0)
				{
					count++;
					flag[3] = 1;
				}
			}
			if (count < 3)
				return false;
			for (int i = 0; i < str.length() - 3;i++)
			{
				string temp(str, i, 3);
				auto pos = str.rfind(temp);
				if (pos != i)
					return false;
			}
			return true;
		}
	};
}


#if 0
int main(){
	nowcoder::Solution sol;
	string str = "))20Uq%0";
	cout << sol.isValidPasswd(str);
	system("pause");
}
#endif