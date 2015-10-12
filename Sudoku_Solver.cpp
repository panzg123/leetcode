class Solution {
public:
    /*Sudoku solver 求解数独 暴力破解 时间复杂度高 
	其它方法：0ms, https://leetcode.com/discuss/59649/yet-another-0ms-c-solution*/
	void solveSudoku(vector<vector<char>>& board)
	{
		solveSudoku_help(board);
	}
	bool solveSudoku_help(vector<vector<char>> &board)
	{
		for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] == '.') {
				for (int k = 0; k < 9; ++k) {
					board[i][j] = '1' + k;
					if (isValidSudoku(board) && solveSudoku_help(board))
						return true;
					board[i][j] = '.';
				}
				return false;
			}
		}
		return true;
	}
	/*Valid Sudoku 运用位运算*/
	bool isValidSudoku(vector<vector<char>>& board)
	{
		//col,row,sqr分别记录每行每列的状态
		int col[9] = {}, row[9] = {}, sqr[9] = {};
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if (board[i][j] != '.'){
					//sq计算出属于第几个格子
					int n = 1 << (board[i][j] - '1'), sq = (i / 3) * 3 + j / 3;
					//与运算判断是否已经出现
					if (row[i] & n || col[j] & n || sqr[sq] & n) return false;
					//或运算，更新出现的数
					row[i] |= n;
					col[j] |= n;
					sqr[sq] |= n;
				}
			}
		}
		return true;
	}
};