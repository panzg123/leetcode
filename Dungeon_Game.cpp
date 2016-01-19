//Dungeon Game,动态规划，重点是从右下角开始循环
int calculateMinimumHP(vector<vector<int>> &dungeon)
{
    int row = dungeon.size();
    int col = dungeon[0].size();
    //res记录节点res[i][j]所需要的最少hp
    vector<vector<int>> res(row+1, vector<int>(col+1, INT_MAX));
    res[row - 1][col] = 1;
    res[row][col - 1] = 1;
    for (int i = row - 1; i >= 0; --i)
    {
        for (int j = col - 1; j >= 0; --j)
        {
            //选择右边或者下边中较小的hp值
            int t = min(res[i + 1][j], res[i][j + 1]) - dungeon[i][j];
            //最小为1
            res[i][j] = max(t, 1);
        }
    }
    //返回左上顶点需要的hp值
    return res[0][0];
}