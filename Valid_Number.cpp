class Solution
{
private:
	/*消除句首和句末的空格符*/
	string& trim(string &s)
	{
		if (s.empty())
		{
			return s;
		}
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
		return s;
	}
public:
	//valid number ,使用自动机
	bool isNumber(string s) 
	{
		char fsm[10][128];
		memset(fsm, 10, sizeof(fsm));
		for (char i = '0'; i <= '9'; i++) 
		{
			fsm[0][i] = 1;
			fsm[1][i] = 1;
			fsm[2][i] = 3;
			fsm[3][i] = 3;
			fsm[5][i] = 3;
			fsm[6][i] = 1;
			fsm[7][i] = 8;
			fsm[8][i] = 8;
			fsm[2][i] = 8;
			fsm[9][i] = 8;
		}
		fsm[0][' '] = 0;
		fsm[1][' '] = 4;
		fsm[3][' '] = 4;
		fsm[4][' '] = 4;
		fsm[8][' '] = 4;
		fsm[1]['e'] = 2;
		fsm[3]['e'] = 7;
		fsm[1]['.'] = 3;
		fsm[0]['.'] = 5;
		fsm[0]['-'] = 6;
		fsm[0]['+'] = 6;
		fsm[6]['.'] = 5;
		fsm[7]['+'] = 9;
		fsm[7]['-'] = 9;
		fsm[2]['+'] = 9;
		fsm[2]['-'] = 9;
		int state = 0;
		for (auto c : s) 
		{
			state = fsm[state][c];
			if (state > 9) 
			{
				return false;
			}
		}
		if (state == 1 || state == 3 || state == 4 || state == 8)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//valid number，使用有限自动机
	bool isNumber_FSM(const char *s)
	{
		enum InputType
		{
			INVALID, // 0
			SPACE, // 1 空格
			SIGN, // 2 正负号
			DIGIT, // 3  数字
			DOT, // 4  点号
			EXPONENT, // 5  指数
			NUM_INPUTS // 6 
		};
		const int transitionTable[][NUM_INPUTS] =
		{
			-1, 0, 3, 1, 2, -1, // next states for state 0
			-1, 8, -1, 1, 4, 5, // next states for state 1
			-1, -1, -1, 4, -1, -1, // next states for state 2
			-1, -1, -1, 1, 2, -1, // next states for state 3
			-1, 8, -1, 4, -1, 5, // next states for state 4
			-1, -1, 6, 7, -1, -1, // next states for state 5
			-1, -1, -1, 7, -1, -1, // next states for state 6
			-1, 8, -1, 7, -1, -1, // next states for state 7
			-1, 8, -1, -1, -1, -1, // next states for state 8
		};
		int state = 0;
		for (; *s != '\0'; ++s)
		{
			InputType inputType = INVALID;
			if (isspace(*s))
				inputType = SPACE;
			else if (*s == '+' || *s == '-')
				inputType = SIGN;
			else if (isdigit(*s))
				inputType = DIGIT;
			else if (*s == '.')
				inputType = DOT;
			else if (*s == 'e' || *s == 'E')
				inputType = EXPONENT;
			// Get next state from current state and input symbol
			state = transitionTable[state][inputType];
			// Invalid input
			if (state == -1) return false;
		}
		// If the current state belongs to one of the accepting (final) states,
		// then the number is valid
		return state == 1 || state == 4 || state == 7 || state == 8;
	}

	/*valid number，使用 strtod库函数*/
	bool isNumber_strtod(string s)
	{
		const char *cstr = s.c_str();
		char *endptr;
		strtod(cstr, &endptr);
		if (endptr == cstr) return false;
		for (;*endptr;++endptr)
		if (!isspace(*endptr)) return false;
		return true;
	}
	/*
	valid number，使用正则表达式匹配
	leetcode不能识别regex
	*/
	bool isNumber_regex(string s) {
		//这里要去除首和末的空白符
		//s = s.trim();
		s = trim(s);
		regex pattern("[+-]?(([0-9]*\\.?[0-9]+)|([0-9]+\\.?[0-9]*))([eE][+-]?[0-9]+)?");
		bool res = regex_match(s, pattern);
		if (res) return true;
		else return false;
	}
}