//Find Median from Data Stream,https://leetcode.com/problems/find-median-from-data-stream/
//时间复杂度为O(logN)
//用两个堆, max heap 和 min heap. 维持两个堆的大小相等(min堆可以比max堆多一个)
//如元素[1,2,3,4,5,6],则max-heap =[-4,-5,-6],min-heap=[3,2,1],所以median=3-(-4)/2=3.5
//如元素[1,2,3,4,5],则max-heap =[-4,-5],min-heap=[3,2,1]，所以median = min-heap.top()=3
class MedianFinder
{
    priority_queue<long> small, large;
public:

    void addNum(int num)
    {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (small.size() < large.size())
        {
            small.push(-large.top());
            large.pop();
        }
    }

    double findMedian()
    {
        return small.size() > large.size()
               ? small.top()
               : (small.top() - large.top()) / 2.0;
    }
};