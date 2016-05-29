//https://leetcode.com/problems/self-crossing/
//数学题，讲解见https://leetcode.com/discuss/89336/best-submission-searching-for-the-crossing-patterns-the-key
//以下三种情况会相交：(1)第i条线，相交于第i-3条线；(2)第i条线，相交于i-4条线，即两线重合；(3)第i条线，相交于第i-5条线
bool isSelfCrossing(vector<int>& x)
{
    size_t size = x.size();
    for (int i = 3; i < size; i++)
    {
        if (x[i] >= x[i - 2] && x[i - 1] <= x[i - 3]) return true;
        if (i >= 4 && x[i - 1] == x[i - 3] && x[i] + x[i - 4] >= x[i - 2]) return true;
        if (i >= 5 && x[i - 2] - x[i - 4] >= 0 && x[i] >= x[i - 2] - x[i - 4] && x[i - 1] >= x[i - 3] - x[i - 5] && x[i - 1] <= x[i - 3]) return true;
    }
    return false;
}