package main

import (
	"math"
	"math/rand"
	"sort"
	"strconv"
	"strings"
	"time"
)

// lengthOfLongestSubstring 无重复字符的最长子串
func lengthOfLongestSubstring(s string) int {
	data := make([]int, 256)
	for i := range data {
		data[i] = -1
	}
	var (
		maxLen   int
		startPos int
		localLen int
	)
	for i, v := range s {
		if data[v] < startPos {
			localLen += 1
		} else {
			localLen = i - data[v]
			startPos = data[v]
		}
		data[v] = i
		if localLen > maxLen {
			maxLen = localLen
		}
	}
	return maxLen
}

type ListNode struct {
	Val  int
	Next *ListNode
}

// reverseList 反转链表
func reverseList(head *ListNode) *ListNode {
	if head == nil {
		return nil
	}
	var (
		pre  *ListNode
		next *ListNode
	)
	for head.Next != nil {
		// 记录下一个节点
		next = head.Next
		// 链接前一个节点
		head.Next = pre
		// 更新当前节点
		pre = head
		head = next
	}
	head.Next = pre
	return head
}

// LRUCache LRU缓存
type LRUCache struct {
	cnt        int
	cap        int
	head       *LRUCacheNode
	tail       *LRUCacheNode
	mapKeyNode map[int]*LRUCacheNode
}

type LRUCacheNode struct {
	key   int
	value int
	next  *LRUCacheNode
	pre   *LRUCacheNode
}

// Constructor 构造LRU
func Constructor(capacity int) LRUCache {
	return LRUCache{
		mapKeyNode: make(map[int]*LRUCacheNode),
		cap:        capacity,
	}
}

func (this *LRUCache) Get(key int) int {
	node, ok := this.mapKeyNode[key]
	if !ok {
		return -1
	}
	// 如果存在，则放在链表头部
	if node.pre != nil {
		node.pre.next = node.next
	}
	if node.next != nil {
		node.next.pre = node.pre
	} else {
		this.tail = node.pre
	}
	node.next = this.head
	node.pre = nil
	this.head = node
	if this.tail == nil {
		this.tail = this.head
	}
	return node.value
}

func (this *LRUCache) Put(key int, value int) {
	node, ok := this.mapKeyNode[key]
	if ok {
		node.value = value
		// 断开
		if node.pre != nil {
			node.pre.next = node.next
		}
		if node.next != nil {
			node.next.pre = node.pre
		} else {
			this.tail = node.pre
		}
		// 头部
		node.next = this.head
		node.pre = nil
		this.head = node
		if this.tail == nil {
			this.tail = this.head
		}
		return
	}
	// 如果不存在
	if this.cnt >= this.cap {
		deleteKey := this.tail.key
		this.tail = this.tail.pre
		this.cnt -= 1
		delete(this.mapKeyNode, deleteKey)
	}
	head := &LRUCacheNode{
		next:  this.head,
		pre:   nil,
		key:   key,
		value: value,
	}
	if this.head != nil {
		this.head.pre = head
	}
	this.head = head
	this.cnt += 1
	if this.tail == nil {
		this.tail = this.head
	}
	this.mapKeyNode[key] = head
}

// generate 118. Pascal’s Triangle #
func generate(numRows int) [][]int {
	var ret [][]int
	for i := 0; i < numRows; i++ {
		var line []int
		for j := 0; j <= i; j++ {
			if j == 0 || j == i {
				line = append(line, 1)
			} else {
				line = append(line, ret[i-1][j-1]+ret[i-1][j])
			}
		}
		ret = append(ret, line)
	}
	return ret
}

// 33. Search in Rotated Sorted Array #
// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4
func search33(nums []int, target int) int {
	// 二分搜索，利用局部有序的特定
	if len(nums) == 0 {
		return -1
	}
	low, high := 0, len(nums)-1
	for low <= high {
		mid := low + (high - low>>1)
		if nums[mid] == target {
			return mid
		}
		// 前半部分递增
		if nums[mid] > nums[low] {
			if target >= nums[low] && target < nums[mid] {
				high = mid - 1
			} else {
				low = mid + 1
			}
		} else if nums[mid] < nums[high] { // 后半部分递增
			if target > nums[mid] && target <= nums[high] {
				low = mid + 1
			} else {
				high = mid - 1
			}
		} else {
			// 边界条件
			if nums[low] == nums[mid] {
				low++
			}
			if nums[high] == nums[mid] {
				high--
			}
		}
	}
	return -1
}

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
// Explanation: 342 + 465 = 807.
func addTwoNumbers(l1 *ListNode, l2 *ListNode) *ListNode {
	var pre = 0
	head := &ListNode{}
	preNode := head
	for l1 != nil || l2 != nil {
		var val1, val2 int
		if l1 != nil {
			val1 = l1.Val
			l1 = l1.Next
		}
		if l2 != nil {
			val2 = l2.Val
			l2 = l2.Next
		}
		preNode.Next = &ListNode{
			Val: (val1 + val2 + pre) % 10,
		}
		pre = (val1 + val2 + pre) / 10
		preNode = preNode.Next
	}
	// 还剩一个进位
	if pre != 0 {
		preNode.Next = &ListNode{
			Val: pre,
		}
	}
	return head.Next
}

// 4. Median of Two Sorted Arrays
// Example:
// nums1 = [1, 2]
// nums2 = [3, 4]
// The median is (2 + 3)/2 = 2.5
func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	if len(nums1) > len(nums2) {
		return findMedianSortedArrays(nums2, nums1)
	}
	// 寻找分割线
	// nums1:  ……………… nums1[mid1-1] | nums1[mid1] ……………………
	// nums2:  ……………… nums2[mid2-1] | nums2[mid2] ……………………
	// 其中mid2 = k - mid1
	// 最终行程交错的形式： ....nums1[mid1-1], nums2[mid2-2], nums1[mid1], nums2[mid2]....
	low, high, k, mid1, mid2 := 0, len(nums1), (len(nums1)+len(nums2)+1)>>1, 0, 0
	for low <= high {
		mid1 = low + (high-low)>>1
		mid2 = k - mid1
		if mid1 > 0 && nums1[mid1-1] > nums2[mid2] {
			// mid1太大，需要左移分割线
			high = mid1 - 1
		} else if mid1 != len(nums1) && nums1[mid1] < nums2[mid2-1] {
			// mid1太小，需要右移分割线
			low = mid1 + 1
		} else {
			// 已找到
			break
		}
	}
	// 返回相应数据
	left, right := 0, 0
	if mid1 == 0 { // 边界条件，前半部分全是nums2
		left = nums2[mid2-1]
	} else if mid2 == 0 {
		left = nums1[mid1-1]
	} else {
		left = max(nums1[mid1-1], nums2[mid2-1])
	}
	if (len(nums1)+len(nums2))%2 == 1 {
		return float64(left)
	}
	if mid1 == len(nums1) { // 边界条件，前半部分全是nums1
		right = nums2[mid2]
	} else if mid2 == len(nums2) {
		right = nums1[mid1]
	} else {
		right = min(nums1[mid1], nums2[mid2])
	}
	return float64(left+right) / 2
}

// 1331. 数组序号转换
// easy
func arrayRankTransform(arr []int) []int {
	if len(arr) == 0 {
		return []int{}
	}
	// 先拷贝一份&排序
	tmp := make([]int, len(arr))
	copy(tmp, arr)
	sort.Ints(tmp)
	// 记录序号
	idx := make(map[int]int)
	var pos int
	for _, v := range tmp {
		if _, ok := idx[v]; !ok {
			idx[v] = pos
			pos++
		}
	}
	// 打印输出
	ret := make([]int, 0, len(arr))
	for _, v := range arr {
		ret = append(ret, idx[v]+1)
	}
	return ret
}

// 5. Longest Palindromic Substring
// Input: s = "babad"
// Output: "bab"
func longestPalindrome(s string) string {
	var res = s[0:1]
	var maxLen = 1
	dp := make([][]bool, len(s))
	for i := 0; i < len(s); i++ {
		dp[i] = make([]bool, len(s))
		dp[i][i] = true
	}
	for i := len(s) - 1; i >= 0; i-- {
		for j := i + 1; j < len(s); j++ {
			if s[i] == s[j] && (j == i+1 || dp[i+1][j-1]) {
				dp[i][j] = true
				if j-i+1 > maxLen {
					maxLen = j - i + 1
					res = s[i : j+1]
				}
			}
		}
	}
	return res
}

// 11. Container With Most Water
// Input: [1,8,6,2,5,4,8,3,7]
// Output: 49
func maxArea(height []int) int {
	i, j := 0, len(height)-1
	var maxRet = math.MinInt
	for i < j {
		maxRet = max(maxRet, min(height[i], height[j])*(j-i))
		if height[i] < height[j] {
			i++
		} else {
			j--
		}
	}
	return maxRet
}

// 593. 有效的正方形
// 输入: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
// 输出: True
func validSquare(p1 []int, p2 []int, p3 []int, p4 []int) bool {
	return false
}

// 15. 3Sum
// Given array nums = [-1, 0, 1, 2, -1, -4],
//
// A solution set is:
// [
//
//	[-1, 0, 1],
//	[-1, -1, 2]
//
// ]
func threeSum(nums []int) [][]int {
	sort.Ints(nums)
	var ret [][]int
	for i := 0; i < len(nums)-2; i++ {
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}
		left, right := i+1, len(nums)-1
		for left < right {
			sum := nums[i] + nums[left] + nums[right]
			if sum == 0 {
				ret = append(ret, []int{nums[i], nums[left], nums[right]})
				for left < right && nums[left+1] == nums[left] {
					left++
				}
				for left < right && nums[right] == nums[right-1] {
					right--
				}
				left++
				right--
			} else if sum > 0 {
				right--
			} else {
				left++
			}
		}
	}
	return ret
}

// 18. 4Sum
// 输入：nums = [1,0,-1,0,-2,2], target = 0
// 输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
// 方案1：双指针，复杂度O(N3)，超时
// 方案2：hash缓存双数之和，平均复杂度O(N2）
func fourSum(nums []int, target int) [][]int {
	sort.Ints(nums)
	// 先计算缓存
	cache := make(map[int][][]int)
	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ {
			val := nums[i] + nums[j]
			// 去重
			needInsert := true
			if vec, ok := cache[val]; ok {
				item := vec[len(vec)-1]
				if nums[item[0]] == nums[i] && nums[item[1]] == nums[j] {
					needInsert = false
				}
			}
			if needInsert {
				cache[val] = append(cache[val], []int{i, j})
			}
		}
	}
	var ret [][]int
	// 寻找匹配的数据
	for i := 0; i < len(nums); i++ {
		for j := i + 1; j < len(nums); j++ {
			left := target - nums[i] - nums[j]
			vec, ok := cache[left]
			if !ok {
				continue
			}
			for _, v := range vec {
				// 必然有i,j > 缓存中的位移，避免重复
				if i <= v[1] {
					continue
				}
				if len(ret) > 0 && ret[len(ret)-1][0] == nums[v[0]] && ret[len(ret)-1][1] == nums[v[1]] &&
					ret[len(ret)-1][2] == nums[i] && ret[len(ret)-1][3] == nums[j] {
					continue
				}
				ret = append(ret, []int{nums[v[0]], nums[v[1]], nums[i], nums[j]})
			}
		}
	}
	// 排序以移除重复数据
	sort.Slice(ret, func(i, j int) bool {
		if ret[i][0] == ret[j][0] {
			if ret[i][1] == ret[j][1] {
				if ret[i][2] == ret[j][2] {
					return ret[i][3] < ret[j][3]
				}
				return ret[i][2] < ret[j][2]
			}
			return ret[i][1] < ret[j][1]
		}
		return ret[i][0] < ret[j][0]
	})
	var uniqueRet [][]int
	for _, v := range ret {
		idx := len(uniqueRet)
		if idx > 0 && v[0] == uniqueRet[idx-1][0] && v[1] == uniqueRet[idx-1][1] &&
			v[2] == uniqueRet[idx-1][2] && v[3] == uniqueRet[idx-1][3] {
			continue
		}
		uniqueRet = append(uniqueRet, v)
	}
	return uniqueRet
}

var (
	letterMap = []string{
		" ",
		"",
		"abc",
		"def",
		"ghi",
		"jkl",
		"mno",
		"pqrs",
		"tuv",
		"wxyz",
	}
)

func letterCombinations(digits string) []string {
	// dfs处理
	if digits == "" {
		return []string{}
	}
	// 先处理后续的
	right := letterCombinations(digits[1:])
	idx := digits[0] - '0'
	letter := letterMap[idx]
	var ret []string
	for _, v := range letter {
		// 最后一个元素右侧无数据
		if len(right) == 0 {
			ret = append(ret, string(v))
			continue
		}
		for _, r := range right {
			ret = append(ret, string(v)+r)
		}
	}
	return ret
}

// 31. 下一个排列
// 输入：nums = [1,2,3]
// 输出：[1,3,2]
func nextPermutation(nums []int) {
	for i := len(nums) - 1; i >= 0; i-- {
		for j := len(nums) - 1; j > i; j-- {
			if nums[i] < nums[j] {
				// 交换
				tmp := nums[i]
				nums[i] = nums[j]
				nums[j] = tmp
				// i之后的元素要排序
				sort.Ints(nums[i+1:])
				return
			}
		}
	}
	// 没有找到，返回最小排序
	sort.Ints(nums)
	return
}

// 46. 全排列
// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
func permute(nums []int) [][]int {
	if len(nums) == 1 {
		return [][]int{{nums[0]}}
	}
	var ret [][]int
	// 递归
	for i := 0; i < len(nums); i++ {
		sliceIntSwap(nums, 0, i)
		right := permute(nums[1:])
		for _, v := range right {
			ret = append(ret, append([]int{nums[0]}, v...))
		}
		sliceIntSwap(nums, 0, i)
	}
	return ret
}

func sliceIntSwap(nums []int, i, j int) {
	tmp := nums[i]
	nums[i] = nums[j]
	nums[j] = tmp
}

// 47. 全排列 II
// 输入：nums = [1,1,2]
// 输出：
// [[1,1,2],
// [1,2,1],
// [2,1,1]]
func permuteUnique(nums []int) [][]int {
	if len(nums) == 1 {
		return [][]int{{nums[0]}}
	}
	// 相同元素排除，因此要求必须有序
	tmp := make([]int, len(nums))
	copy(tmp, nums)
	sort.Ints(tmp)
	var ret [][]int
	// 递归
	for i := 0; i < len(tmp); i++ {
		// 边界条件1：相同元素不调换
		// 边界条件2：排序后的连续相同元素，只调换第一个
		if i != 0 && (tmp[i] == tmp[0] || tmp[i-1] == tmp[i]) {
			continue
		}
		sliceIntSwap(tmp, 0, i)
		right := permuteUnique(tmp[1:])
		for _, v := range right {
			ret = append(ret, append([]int{tmp[0]}, v...))
		}
		sliceIntSwap(tmp, 0, i)
	}
	return ret
}

// 394. Decode String
// s = "3[a2[c]]", return "accaccacc".
func decodeString(s string) string {
	var (
		stack []string
		ret   string
	)
	for _, v := range s {
		if v != ']' {
			// 直接入栈
			stack = append(stack, string(v))
		} else {
			// 出栈，计算字符串
			var tmp string
			for len(stack) > 0 && stack[len(stack)-1] != "[" {
				tmp = stack[len(stack)-1] + tmp
				stack = stack[:len(stack)-1]
			}
			// 移除[符号
			stack = stack[:len(stack)-1]
			// 计算数字
			var number string
			for len(stack) > 0 && stack[len(stack)-1] >= "0" && stack[len(stack)-1] <= "9" {
				number = stack[len(stack)-1] + number
				stack = stack[:len(stack)-1]
			}
			numberInt, _ := strconv.Atoi(number)
			for i := 0; i < numberInt; i++ {
				stack = append(stack, tmp)
			}
		}
	}
	// 计算ret
	for _, v := range stack {
		ret += v
	}
	return ret
}

// 1374. 生成每种字符都是奇数个的字符串
func generateTheString(n int) string {
	if n%2 == 1 {
		return strings.Repeat("a", n)
	}
	return strings.Repeat("a", n-1) + "b"
}

// 739. Daily Temperatures
// 输入: temperatures = [73,74,75,71,69,72,76,73]
// 输出: [1,1,4,2,1,1,0,0]
func dailyTemperatures(temperatures []int) []int {
	res := make([]int, len(temperatures))
	var stack []int
	for i, v := range temperatures {
		for len(stack) > 0 && temperatures[stack[len(stack)-1]] < v {
			idx := stack[len(stack)-1]
			res[idx] = i - idx
			stack = stack[:len(stack)-1]
		}
		stack = append(stack, i)
	}
	return res
}

// 39. 组合总和
// 输入：candidates = [2,3,6,7], target = 7
// 输出：[[2,2,3],[7]]
func combinationSum(candidates []int, target int) [][]int {
	sort.Ints(candidates)
	return combinationSumHelper(candidates, target)
}

func combinationSumHelper(candidates []int, target int) [][]int {
	var ret [][]int
	for i, v := range candidates {
		if target > v {
			right := combinationSumHelper(candidates[i:], target-v)
			for _, r := range right {
				ret = append(ret, append([]int{v}, r...))
			}
		} else if target == v {
			ret = append(ret, []int{v})
		}
	}
	return ret
}

// 40. Combination Sum II
// Input: candidates = [10,1,2,7,6,1,5], target = 8,
// A solution set is:
// [
//
//	[1, 7],
//	[1, 2, 5],
//	[2, 6],
//	[1, 1, 6]
//
// ]
func combinationSum2(candidates []int, target int) [][]int {
	sort.Ints(candidates)
	return combinationSum2Helper(candidates, target)
}

func combinationSum2Helper(candidates []int, target int) [][]int {
	var ret [][]int
	for i, v := range candidates {
		// 此条件为去重的关键步骤，本次不取重复数字，下次循环可能会取重复数字
		if i > 0 && candidates[i-1] == candidates[i] {
			continue
		}
		if target > v {
			right := combinationSum2Helper(candidates[i+1:], target-v)
			for _, r := range right {
				ret = append(ret, append([]int{v}, r...))
			}
		} else if target == v {
			ret = append(ret, []int{v})
		}
	}
	return ret
}

// 216. Combination Sum III
func combinationSum3(k int, n int) [][]int {
	candidates := []int{1, 2, 3, 4, 5, 6, 7, 8, 9}
	return combinationSum3Helper(candidates, k, n)
}

func combinationSum3Helper(candidates []int, k int, n int) [][]int {
	var ret [][]int
	if k <= 0 || n <= 0 {
		return ret
	}
	for i, v := range candidates {
		// 跳出循环
		if v > n {
			return ret
		}
		if v == n && k == 1 {
			ret = append(ret, []int{v})
			return ret
		}
		// 选中
		right := combinationSum3Helper(candidates[i+1:], k-1, n-v)
		for _, r := range right {
			ret = append(ret, append([]int{v}, r...))
		}
	}
	return ret
}

// 377. Combination Sum IV
// Input: nums = [1,2,3], target = 4
// Output: 7
// Explanation:
// The possible combination ways are:
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)
// Note that different sequences are counted as different combinations.
func combinationSum4(nums []int, target int) int {
	dp := make([]int, target+1)
	dp[0] = 1
	for i := 1; i <= target; i++ {
		for j := 0; j < len(nums); j++ {
			if i >= nums[j] {
				dp[i] += dp[i-nums[j]]
			}
		}
	}
	return dp[target]
}

// 36. 有效的数独
func isValidSudoku(board [][]byte) bool {
	used := make([]bool, 9)
	// 检查行和列
	for i := 0; i < 9; i++ {
		// 重新初始化数据
		for k := range used {
			used[k] = false
		}
		for j := 0; j < 9; j++ {
			if !checkSudoku(used, board[i][j]) {
				return false
			}
		}
		for k := range used {
			used[k] = false
		}
		for j := 0; j < 9; j++ {
			if !checkSudoku(used, board[j][i]) {
				return false
			}
		}
	}
	// 检查四边形区域
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			for k := range used {
				used[k] = false
			}
			for m := 3 * i; m < 3*i+3; m++ {
				for n := 3 * j; n < 3*j+3; n++ {
					if !checkSudoku(used, board[m][n]) {
						return false
					}
				}
			}
		}
	}
	return true
}

func checkSudoku(used []bool, c byte) bool {
	if c == '.' {
		return true
	}
	if used[c-'1'] == true {
		return false
	}
	used[c-'1'] = true
	return true
}

// 416. 分割等和子集
// 输入：nums = [1,5,11,5]
// 输出：true
// 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
func canPartition(nums []int) bool {
	var sum int
	for _, v := range nums {
		sum += v
	}
	if sum%2 != 0 {
		return false
	}
	w := sum / 2
	dp := make([]bool, w+1)
	dp[0] = true
	for _, v := range nums {
		for i := w; i >= v; i-- {
			dp[i] = dp[i] || dp[i-v]
		}
	}
	return dp[w]
}

// 494. 目标和
// 输入：nums = [1,1,1,1,1], target = 3
// 输出：5
// 解释：一共有 5 种方法让最终目标和为 3 。
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3
func findTargetSumWays(nums []int, target int) int {
	var sum int
	for _, v := range nums {
		sum += v
	}
	if sum < target || ((sum+target)%2 == 1) {
		return 0
	}
	w := (sum + target) / 2
	dp := make([]int, w+1)
	dp[0] = 1
	for _, v := range nums {
		for i := w; i >= v; i-- {
			dp[i] = dp[i] + dp[i-v]
		}
	}
	return dp[w]
}

func hammingDistance(x int, y int) int {
	var cnt int
	for x != 0 || y != 0 {
		if x%2 != y%2 {
			cnt++
		}
		x >>= 1
		y >>= 1
	}
	return cnt

	// 方法2，异或，然后才用s &= s-1
	// var cnt int
	// for s := x ^ y; s > 0; s &= s - 1 {
	// 	cnt++
	// }

	// 方法3
	// return bits.OnesCount(uint(x ^ y))
}

func searchRange(nums []int, target int) []int {
	return []int{searchFirstEqualElement(nums, target), searchLastEqualElement(nums, target)}
}

// 二分查找第一个与 target 相等的元素，时间复杂度 O(logn)
func searchFirstEqualElement(nums []int, target int) int {
	var (
		left  = 0
		right = len(nums) - 1
	)
	for left <= right {
		mid := left + (right-left)>>1
		if nums[mid] < target {
			left = mid + 1
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			if mid == 0 || nums[mid-1] < target {
				return mid
			}
			right = mid - 1
		}
	}
	return -1
}

// 二分查找最后一个与 target 相等的元素，时间复杂度 O(logn)
func searchLastEqualElement(nums []int, target int) int {
	var (
		left  = 0
		right = len(nums) - 1
	)
	for left <= right {
		mid := left + (right-left)>>1
		if nums[mid] < target {
			left = mid + 1
		} else if nums[mid] > target {
			right = mid - 1
		} else {
			if mid == len(nums)-1 || nums[mid+1] > target {
				return mid
			}
			left = mid + 1
		}
	}
	return -1
}

// rotate 48. 旋转图像
// 给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
// 思路：先左下右上对称转换，再上下转换
func rotate(matrix [][]int) {
	if len(matrix) == 0 {
		return
	}
	// 斜向转换
	size := len(matrix[0])
	for i := range matrix {
		for j := 0; j < size-i-1; j++ {
			tmp := matrix[i][j]
			matrix[i][j] = matrix[size-j-1][size-i-1]
			matrix[size-j-1][size-i-1] = tmp
		}
	}
	// 上下转换
	for i := 0; i < (len(matrix) / 2); i++ {
		for j := 0; j < size; j++ {
			tmp := matrix[i][j]
			matrix[i][j] = matrix[size-i-1][j]
			matrix[size-i-1][j] = tmp
		}
	}
}

// 49. 字母异位词分组
// 模拟：排序+hash
func groupAnagrams(strs []string) [][]string {
	var ret [][]string
	mapStr := make(map[string][]string)
	for _, v := range strs {
		// 当然这里也可以不用排序，直接用hash或者string转换key，时间复杂度进一步优化
		sortV := []byte(v)
		sort.Slice(sortV, func(i, j int) bool {
			return sortV[i] < sortV[j]
		})
		sortVStr := string(sortV)
		mapStr[sortVStr] = append(mapStr[sortVStr], v)
	}
	for _, v := range mapStr {
		ret = append(ret, v)
	}
	return ret
}

// 64. 最小路径和
// 输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
// 输出：7
// 解释：因为路径 1→3→1→1→1 的总和最小。
func minPathSum(grid [][]int) int {
	if len(grid) == 0 || len(grid[0]) == 0 {
		return 0
	}
	// 声明i*j大小的数组
	var dp = make([][]int, len(grid))
	for i := range grid {
		dp[i] = make([]int, len(grid[0]))
	}
	dp[0][0] = grid[0][0]
	// 首行元素
	for j := 1; j < len(grid[0]); j++ {
		dp[0][j] = dp[0][j-1] + grid[0][j]
	}
	// 首列元素
	for i := 1; i < len(grid); i++ {
		dp[i][0] = dp[i-1][0] + grid[i][0]
	}
	for i := 1; i < len(grid); i++ {
		for j := 1; j < len(grid[0]); j++ {
			dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
		}
	}
	return dp[len(grid)-1][len(grid[0])-1]
}

// minPathSumV2 如上题，内存优化，二维数组压缩到一维
func minPathSumV2(grid [][]int) int {
	var dp = make([]int, len(grid[0]))
	dp[0] = grid[0][0]
	// 首行元素
	for j := 1; j < len(grid[0]); j++ {
		dp[j] = dp[j-1] + grid[0][j]
	}
	// 正常元素
	for i := 1; i < len(grid); i++ {
		for j := 0; j < len(grid[0]); j++ {
			if j == 0 {
				dp[0] = dp[0] + grid[i][j]
				continue
			}
			dp[j] = min(dp[j-1], dp[j]) + grid[i][j]
		}
	}
	return dp[len(grid[0])-1]
}

// 55. 跳跃游戏
// 输入：nums = [2,3,1,1,4]
// 输出：true
// 解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
func canJump(nums []int) bool {
	var mostStep int
	for i, v := range nums {
		if mostStep >= i {
			mostStep = max(i+v, mostStep)
			if mostStep >= len(nums)-1 {
				return true
			}
		}
	}
	return false
}

// 45. 跳跃游戏 II
// 贪心 或者 dp
func jump(nums []int) int {
	dp := make([]int, len(nums))
	for i := range nums {
		dp[i] = math.MaxInt
	}
	dp[0] = 0
	for i := 0; i < len(nums); i++ {
		for j := 0; j < i; j++ {
			if nums[j] >= i-j {
				dp[i] = min(dp[j]+1, dp[i])
			}
		}
	}
	return dp[len(nums)-1]
}

// 53. 最大子数组和
// 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
// 输出：6
// 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
func maxSubArray(nums []int) int {
	maxSum, curSum := math.MinInt, 0
	for _, v := range nums {
		curSum += v
		if curSum > maxSum {
			maxSum = curSum
		}
		if curSum < 0 {
			curSum = 0
		}
	}
	return maxSum
}

// merge 56. 合并区间
func merge(intervals [][]int) [][]int {
	// 排序
	sort.Slice(intervals, func(i, j int) bool {
		if intervals[i][0] == intervals[j][0] {
			return intervals[i][1] < intervals[j][1]
		}
		return intervals[i][0] < intervals[j][0]
	})
	var ret [][]int
	last := intervals[0]
	for i := 1; i < len(intervals); i++ {
		// 两者有交集，则直接合并
		if last[1] >= intervals[i][0] {
			last[1] = max(last[1], intervals[i][1])
		} else {
			ret = append(ret, last)
			last = intervals[i]
		}
	}
	ret = append(ret, last)
	return ret
}

// minDistance 72. 编辑距离
func minDistance(word1 string, word2 string) int {
	if word1 == "" {
		return len(word2)
	}
	if word2 == "" {
		return len(word1)
	}
	var dp = make([][]int, len(word2)+1)
	for i := 0; i < len(word2)+1; i++ {
		dp[i] = make([]int, len(word1)+1)
	}
	// 首行首列要处理
	for i := 0; i < len(word1)+1; i++ {
		dp[0][i] = i
	}
	for i := 0; i < len(word2)+1; i++ {
		dp[i][0] = i
	}
	// 计算
	for i := 1; i <= len(word2); i++ {
		for j := 1; j <= len(word1); j++ {
			if word1[j-1] == word2[i-1] {
				dp[i][j] = dp[i-1][j-1]
			} else {
				dp[i][j] = min(min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]) + 1
			}
		}
	}
	return dp[len(word2)][len(word1)]
}

// 75. 颜色分类
func sortColors(nums []int) {
	p0, p2 := 0, len(nums)-1
	for i := 0; i <= p2; i++ {
		for ; i <= p2 && nums[i] == 2; p2-- {
			nums[i], nums[p2] = nums[p2], nums[i]
		}
		if nums[i] == 0 {
			nums[i], nums[p0] = nums[p0], nums[i]
			p0++
		}
	}
}

// TreeNode 二叉树节点
type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

// 105 前序和中序构建二叉树
func buildTree(preorder []int, inorder []int) *TreeNode {
	if len(preorder) == 0 || len(inorder) == 0 {
		return nil
	}
	root := &TreeNode{
		Val: preorder[0],
	}
	for i, v := range inorder {
		if v == preorder[0] {
			root.Left = buildTree(preorder[1:i+1], inorder[:i])
			root.Right = buildTree(preorder[i+1:], inorder[i+1:])
		}
	}
	return root
}

// 148. 排序链表
func sortList(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	// 找到中间节点，并断开节点
	middle := middleNode(head)
	next := middle.Next
	middle.Next = nil
	middle = next
	left := sortList(head)
	right := sortList(middle)
	// 归并排序左和右
	return mergeTwoLists(left, right)
}

// 76. 最小覆盖子串  滑动窗口
func minWindow(s string, t string) string {
	minLen := math.MaxInt
	var minLeft, minRight = -1, -1
	maps := make(map[byte]int)
	mapt := make(map[byte]int)
	for i := range t {
		mapt[t[i]]++
	}
	check := func() bool {
		for k, v := range mapt {
			if maps[k] < v {
				return false
			}
		}
		return true
	}
	for left, right := 0, 0; right < len(s); right++ {
		// 先统计右指针的字符
		if _, ok := mapt[s[right]]; ok {
			maps[s[right]]++
		}
		// 如果满足条件，则left右移，否则right右移
		for check() && left <= right {
			if right-left+1 < minLen {
				minLen = right - left + 1
				minLeft, minRight = left, right
			}
			if _, ok := mapt[s[left]]; ok {
				maps[s[left]]--
			}
			left++
		}
	}
	if minLeft == -1 {
		return ""
	}
	return s[minLeft : minRight+1]
}

// 876. 链表的中间结点
func middleNode(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return head
	}
	p1 := head
	p2 := head
	for p2.Next != nil && p2.Next.Next != nil {
		p1 = p1.Next
		p2 = p2.Next.Next
	}
	return p1
}

// 21. 合并两个有序链表
func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
	dumty := &ListNode{Val: 1}
	pre := dumty
	for l1 != nil && l2 != nil {
		if l1.Val < l2.Val {
			pre.Next = l1
			l1 = l1.Next
		} else {
			pre.Next = l2
			l2 = l2.Next
		}
		pre = pre.Next
	}
	if l1 != nil {
		pre.Next = l1
	}
	if l2 != nil {
		pre.Next = l2
	}
	return dumty.Next
}

// 78. 子集
// 输入：nums = [1,2,3]
// 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
func subsets(nums []int) [][]int {
	if len(nums) == 0 {
		return nil
	}
	if len(nums) == 1 {
		return [][]int{{}, {nums[0]}}
	}
	var ret [][]int
	right := subsets(nums[1:])
	for _, v := range right {
		// 选择
		ret = append(ret, append([]int{nums[0]}, v...))
		// 不选择
		ret = append(ret, v)
	}
	return ret
}

// 79. 单词搜索
func exist(board [][]byte, word string) bool {
	if len(board) == 0 || len(board[0]) == 0 {
		return false
	}
	visited := make([][]bool, len(board))
	for i, v := range board {
		visited[i] = make([]bool, len(v))
	}
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			if existDfs(board, word, i, j, 0, visited) {
				return true
			}
		}
	}
	return false
}

func existDfs(board [][]byte, word string, x, y, index int, visited [][]bool) bool {
	// 边界条件
	if x < 0 || y < 0 || x >= len(board) || y >= len(board[0]) {
		return false
	}
	// 是否已经访问过
	if visited[x][y] {
		return false
	}
	// 不相等，剪枝
	if board[x][y] != word[index] {
		return false
	}
	// 判断是否最后一个
	if index == len(word)-1 {
		return true
	}

	// 继续递归
	visited[x][y] = true
	ret := existDfs(board, word, x-1, y, index+1, visited) ||
		existDfs(board, word, x+1, y, index+1, visited) ||
		existDfs(board, word, x, y-1, index+1, visited) ||
		existDfs(board, word, x, y+1, index+1, visited)
	visited[x][y] = false
	return ret
}

// DicNode 字典树前缀
type DicNode struct {
	end  bool
	next []*DicNode
}

func (d *DicNode) Init() {
	d.next = make([]*DicNode, 26)
}

// 212. 单词搜索 II
func findWords(board [][]byte, words []string) []string {
	// 构造前缀树
	root := &DicNode{}
	root.Init()
	for _, v := range words {
		cur := root
		for _, w := range v {
			if cur.next[w-'a'] == nil {
				cur.next[w-'a'] = &DicNode{}
				cur.next[w-'a'].Init()
			}
			cur = cur.next[w-'a']
		}
		cur.end = true
	}
	// dfs遍历
	if len(board) == 0 || len(board[0]) == 0 {
		return nil
	}
	visited := make([][]bool, len(board))
	for i, v := range board {
		visited[i] = make([]bool, len(v))
	}
	// map保存结果
	result := make(map[string]bool)
	for i := 0; i < len(board); i++ {
		for j := 0; j < len(board[0]); j++ {
			// 剪枝
			if root.next[board[i][j]-'a'] != nil {
				findWordsDfs(board, root.next[board[i][j]-'a'], visited, i, j, "", result)
			}
		}
	}
	// 结果排序
	var ret []string
	for k := range result {
		ret = append(ret, k)
	}
	sort.Slice(ret, func(i, j int) bool {
		return ret[i] < ret[j]
	})
	return ret
}

func findWordsDfs(board [][]byte, root *DicNode, visited [][]bool, x, y int, curWord string, result map[string]bool) {
	curWord += string(board[x][y])
	if root.end {
		if _, ok := result[curWord]; !ok {
			result[curWord] = true
		}
	}
	visited[x][y] = true
	// 上
	if x > 0 && !visited[x-1][y] && root.next[board[x-1][y]-'a'] != nil {
		findWordsDfs(board, root.next[board[x-1][y]-'a'], visited, x-1, y, curWord, result)
	}
	// 下
	if x < len(board)-1 && !visited[x+1][y] && root.next[board[x+1][y]-'a'] != nil {
		findWordsDfs(board, root.next[board[x+1][y]-'a'], visited, x+1, y, curWord, result)
	}
	// 左
	if y > 0 && !visited[x][y-1] && root.next[board[x][y-1]-'a'] != nil {
		findWordsDfs(board, root.next[board[x][y-1]-'a'], visited, x, y-1, curWord, result)
	}
	// 右
	if y < len(board[0])-1 && !visited[x][y+1] && root.next[board[x][y+1]-'a'] != nil {
		findWordsDfs(board, root.next[board[x][y+1]-'a'], visited, x, y+1, curWord, result)
	}
	visited[x][y] = false
}

// 84. 柱状图中最大的矩形
// 单调栈+哨兵
func largestRectangleArea(heights []int) int {
	if len(heights) == 0 {
		return 0
	}
	// 前后添加哨兵0
	heights = append([]int{0}, heights...)
	heights = append(heights, 0)
	var stack []int
	var maxArea int
	for i := 0; i < len(heights); {
		// 压入单调栈
		if len(stack) == 0 || heights[i] >= heights[stack[len(stack)-1]] {
			stack = append(stack, i)
			i++
		} else {
			// 弹出时计算新栈构成的矩阵面积
			high := heights[stack[len(stack)-1]]
			stack = stack[0 : len(stack)-1]
			// 左边界是栈中新栈顶元素，即数组中第一个比height[i]小的元素位置
			width := i - stack[len(stack)-1] - 1
			maxArea = max(maxArea, high*width)
		}
	}
	return maxArea
}

// 85. 最大矩形
// 利用84题的解法
func maximalRectangle(matrix [][]byte) int {
	if len(matrix) == 0 || len(matrix[0]) == 0 {
		return 0
	}
	height := make([]int, len(matrix[0]))
	var maxArea int
	for i := 0; i < len(matrix); i++ {
		for j := 0; j < len(matrix[0]); j++ {
			if matrix[i][j] == 1 {
				height[j] += 1
			} else {
				height[j] = 0
			}
		}
		maxArea = max(maxArea, largestRectangleArea(height))
	}
	return maxArea
}

// 221. 最大正方形
// 动态规划: dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1 含义为i,j位置的最大矩形
func maximalSquare(matrix [][]byte) int {
	// 边界条件
	if len(matrix) == 0 || len(matrix[0]) == 0 {
		return 0
	}
	dp := make([][]int, len(matrix))
	for i, v := range matrix {
		dp[i] = make([]int, len(v))
	}
	var maxLen int
	for i := 0; i < len(matrix); i++ {
		for j := 0; j < len(matrix[0]); j++ {
			if matrix[i][j] == '1' {
				if i == 0 || j == 0 {
					dp[i][j] = 1
				} else {
					dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1
				}
				maxLen = max(maxLen, dp[i][j])
			}
		}
	}
	return maxLen * maxLen
}

// 764. 最大加号标志
// 动态规划： 上下左右四个方向都要统计
func orderOfLargestPlusSign(n int, mines [][]int) int {
	dp := make([][]int, n)
	for i := 0; i < n; i++ {
		dp[i] = make([]int, n)
	}
	// 处理mine中的0，这里dp默认值为0，所以这里赋值为-1
	for _, v := range mines {
		dp[v[0]][v[1]] = -1
	}
	var maxK int
	// 上和下
	for i := 0; i < n; i++ {
		var cnt int
		for j := 0; j < n; j++ {
			if dp[i][j] == -1 {
				cnt = 0
			} else {
				cnt++
				dp[i][j] = cnt
			}
		}
		cnt = 0
		for j := n - 1; j >= 0; j-- {
			if dp[i][j] == -1 {
				cnt = 0
			} else {
				cnt++
				dp[i][j] = min(dp[i][j], cnt)
			}
		}
	}
	// 左和右
	for j := 0; j < n; j++ {
		var cnt int
		for i := 0; i < n; i++ {
			if dp[i][j] == -1 {
				cnt = 0
			} else {
				cnt++
				dp[i][j] = min(dp[i][j], cnt)
			}
		}
		cnt = 0
		for i := n - 1; i >= 0; i-- {
			if dp[i][j] == -1 {
				cnt = 0
			} else {
				cnt++
				dp[i][j] = min(dp[i][j], cnt)
			}
			maxK = max(maxK, dp[i][j])
		}
	}
	return maxK
}

// 94. 二叉树的中序遍历--栈
func inorderTraversal(root *TreeNode) []int {
	var ret []int
	var stack []*TreeNode
	for len(stack) > 0 || root != nil {
		// 左子树一直入栈
		for root != nil {
			stack = append(stack, root)
			root = root.Left
		}
		// 弹出并打印
		root = stack[len(stack)-1]
		ret = append(ret, stack[len(stack)-1].Val)
		stack = stack[:len(stack)-1]
		root = root.Right
	}
	return ret
}

// 96. 不同的二叉搜索树
// 动态规划，状态转移方程：F(i,n) = dp[i-1] * dp[n-i]，以i为根节点，i-1为左子树，n-i为右子树
// dp[i] = dp[0]*dp[i-1] + dp[1]*dp[i-2] + dp[2]*dp[i-3] + ... + dp[j]*dp[i-j-1]
func numTrees(n int) int {
	dp := make([]int, n+1)
	dp[0] = 1 // 空节点
	dp[1] = 1 // 单节点
	for i := 2; i <= n; i++ {
		for j := 1; j <= i; j++ {
			dp[i] += dp[j-1] * dp[i-j]
		}
	}
	return dp[n]
}

// 101. 对称二叉树
// 递归解决方案
func isSymmetric(root *TreeNode) bool {
	if root == nil {
		return true
	}
	return isSymmetricHelper(root.Left, root.Right)
}

func isSymmetricHelper(left *TreeNode, right *TreeNode) bool {
	if left == nil && right == nil {
		return true
	}
	if left == nil || right == nil {
		return false
	}
	return left.Val == right.Val && isSymmetricHelper(left.Right, right.Left) &&
		isSymmetricHelper(left.Left, right.Right)
}

// 101. 对称二叉树
// 非递归，栈
func isSymmetricWithStack(root *TreeNode) bool {
	if root == nil {
		return true
	}
	var queue []*TreeNode
	queue = append(queue, root)
	queue = append(queue, root)
	for len(queue) > 0 {
		left := queue[0]
		right := queue[1]
		queue = queue[2:]
		if left == nil && right == nil {
			continue
		}
		if left == nil || right == nil {
			return false
		}
		if left.Val != right.Val {
			return false
		}
		// 左子树的左节点 + 右子树的有节点
		queue = append(queue, left.Left)
		queue = append(queue, right.Right)
		// 左子树的右节点 + 右子树的左节点
		queue = append(queue, left.Right)
		queue = append(queue, right.Left)
	}
	return true
}

// 102. 二叉树的层序遍历
// 双层队列
func levelOrder(root *TreeNode) [][]int {
	if root == nil {
		return nil
	}
	var cur []*TreeNode
	var ret [][]int
	cur = append(cur, root)
	for len(cur) > 0 {
		var line []int
		var next []*TreeNode
		for len(cur) > 0 {
			line = append(line, cur[0].Val)
			if cur[0].Left != nil {
				next = append(next, cur[0].Left)
			}
			if cur[0].Right != nil {
				next = append(next, cur[0].Right)
			}
			cur = cur[1:]
		}
		ret = append(ret, line)
		cur = next
	}
	return ret
}

// 104. 二叉树的最大深度
func maxDepth(root *TreeNode) int {
	if root == nil {
		return 0
	}
	return max(maxDepth(root.Left), maxDepth(root.Right)) + 1
}

// 114. 二叉树展开为链表
// 递归解法
func flatten(root *TreeNode) {
	if root == nil {
		return
	}
	// 保存临时节点
	right := root.Right
	// 左子树递归
	flatten(root.Left)
	root.Right = root.Left
	root.Left = nil
	// 遍历到最右末端节点
	cur := root
	for cur.Right != nil {
		cur = cur.Right
	}
	// 右子树递归
	flatten(right)
	cur.Right = right
	return
}

// 124. 二叉树中的最大路径和
func maxPathSum(root *TreeNode) int {
	maxPath := math.MinInt
	maxPathSumHelper(root, &maxPath)
	return maxPath
}

// maxPathSumHelper 参数maxPath 全局最大路径和，返回值是以根节点为其实的最大路径和
func maxPathSumHelper(root *TreeNode, maxPath *int) int {
	if root == nil {
		return 0
	}
	rootVal := root.Val
	leftRootVal := maxPathSumHelper(root.Left, maxPath)
	rightRootVal := maxPathSumHelper(root.Right, maxPath)
	if leftRootVal > 0 {
		rootVal += leftRootVal
	}
	if rightRootVal > 0 {
		rootVal += rightRootVal
	}
	// 更新全局最大值
	if rootVal > *maxPath {
		*maxPath = rootVal
	}
	// 更新包含根节点的最大路径和
	maxRootVal := max(leftRootVal, rightRootVal)
	if maxRootVal > 0 {
		return root.Val + maxRootVal
	}
	return root.Val
}

// 112. 路径总和
func hasPathSum(root *TreeNode, targetSum int) bool {
	if root == nil {
		return false
	}
	if root.Left == nil && root.Right == nil {
		return root.Val == targetSum
	}
	return hasPathSum(root.Right, targetSum-root.Val) || hasPathSum(root.Left, targetSum-root.Val)
}

// 113. 路径总和 II
func pathSum(root *TreeNode, targetSum int) [][]int {
	var ret [][]int
	var path []int
	var dfs func(*TreeNode, int)
	dfs = func(node *TreeNode, left int) {
		if node == nil {
			return
		}
		// 当前节点
		left -= node.Val
		path = append(path, node.Val)
		// 移除选择的节点，path为闭包变量
		defer func() {
			path = path[:len(path)-1]
		}()
		// 满足条件
		if node.Left == nil && node.Right == nil && left == 0 {
			ret = append(ret, append([]int{}, path...))
			return
		}
		dfs(node.Left, left)
		dfs(node.Right, left)
	}
	dfs(root, targetSum)
	return ret
}

// 437. 路径总和 III
// dfs+遍历所有节点
func pathSum437(root *TreeNode, targetSum int) int {
	var ret int
	var dfs func(*TreeNode, int)
	dfs = func(node *TreeNode, left int) {
		if node == nil {
			return
		}
		// 当前节点
		left -= node.Val
		if left == 0 {
			ret += 1
		}
		dfs(node.Left, left)
		dfs(node.Right, left)
	}
	if root == nil {
		return 0
	}
	dfs(root, targetSum)
	return ret + pathSum437(root.Left, targetSum) + pathSum437(root.Right, targetSum)
}

// 129. 求根节点到叶节点数字之和
// dfs
func sumNumbers(root *TreeNode) int {
	var ret int
	var dfs func(*TreeNode, int)
	dfs = func(node *TreeNode, sum int) {
		if node == nil {
			return
		}
		sum = sum*10 + node.Val
		if node.Left == nil && node.Right == nil {
			ret += sum
		}
		dfs(node.Left, sum)
		dfs(node.Right, sum)
	}
	dfs(root, 0)
	return ret
}

// 687. 最长同值路径
func longestUnivaluePath(root *TreeNode) int {
	var ret int
	// 以root为根节点为相同值的最大路径
	var dfs func(node *TreeNode) int
	dfs = func(node *TreeNode) int {
		if node == nil {
			return 0
		}
		left := dfs(node.Left)
		right := dfs(node.Right)
		var left1, right1 int
		if node.Left != nil && node.Left.Val == node.Val {
			left1 = left + 1
		}
		if node.Right != nil && node.Right.Val == node.Val {
			right1 = right + 1
		}
		if left1+right1 > ret {
			ret = left1 + right1
		}
		return max(left1, right1)
	}
	dfs(root)
	return ret
}

// 121. 买卖股票的最佳时机
func maxProfit(prices []int) int {
	minprice := prices[0]
	res := 0
	for _, v := range prices {
		res = max(res, v-minprice)
		minprice = min(v, minprice)
	}
	return res
}

// 买卖股票的最佳时机 II
func maxProfitV2(prices []int) int {
	var res int
	for i := 0; i < len(prices)-1; i++ {
		if prices[i] < prices[i+1] {
			res += prices[i+1] - prices[i]
		}
	}
	return res
}

// 123. 买卖股票的最佳时机 III
func maxProfitV3(prices []int) int {

	return 0
}

// 128. 最长连续序列
func longestConsecutive(nums []int) int {
	visit := make(map[int]bool)
	data := make(map[int]bool)
	for _, v := range nums {
		data[v] = true
	}
	var maxLen int
	for _, v := range nums {
		if _, ok := visit[v]; ok {
			continue
		}
		var tmpLen int
		// 向左拓展
		for j := v; true; j-- {
			if _, ok := data[j]; !ok {
				break
			}
			tmpLen++
			visit[j] = true
		}
		// 向右拓展
		for j := v + 1; true; j++ {
			if _, ok := data[j]; !ok {
				break
			}
			tmpLen++
			visit[j] = true
		}
		maxLen = max(maxLen, tmpLen)
	}
	return maxLen
}

// 136. 只出现一次的数字
func singleNumber(nums []int) int {
	var ret int
	for _, v := range nums {
		ret ^= v
	}
	return ret
}

// 139. 单词拆分
func wordBreak(s string, wordDict []string) bool {
	wordMap := make(map[string]bool)
	for _, v := range wordDict {
		wordMap[v] = true
	}
	dp := make([]bool, len(s)+1)
	dp[0] = true
	for i := 1; i <= len(s); i++ {
		for j := 0; j < i; j++ {
			if dp[j] {
				word := s[j:i]
				if _, ok := wordMap[word]; ok {
					dp[i] = true
				}
			}
		}
	}
	return dp[len(s)]
}

// 140. 单词拆分 II
func wordBreakV2(s string, wordDict []string) []string {
	if s == "" {
		return nil
	}
	var res []string
	for _, v := range wordDict {
		if !strings.HasPrefix(s, v) {
			continue
		}
		left := s[len(v):]
		if left == "" {
			res = append(res, v)
			continue
		}
		subRes := wordBreakV2(left, wordDict)
		for _, v1 := range subRes {
			res = append(res, v+""+v1)
		}
	}
	return res
}

// 141. 环形链表
func hasCycle(head *ListNode) bool {
	if head == nil || head.Next == nil {
		return false
	}
	fast := head
	slow := head
	for slow != nil && slow.Next != nil {
		fast = fast.Next
		slow = slow.Next.Next
		if fast == slow {
			return true
		}
	}
	return false
}

// 142. 环形链表 II
func detectCycle(head *ListNode) *ListNode {
	if head == nil || head.Next == nil {
		return nil
	}
	fast := head
	slow := head
	slow1 := head
	for slow != nil && slow.Next != nil {
		fast = fast.Next
		slow = slow.Next.Next
		if fast == slow {
			// 两个慢节点重新相遇处即为环的入口
			for slow1 != slow {
				slow = slow.Next
				slow1 = slow1.Next
			}
			return slow
		}
	}
	return nil
}

// 152. 乘积最大子数组
// 思路：由于负数的存在，需要同时保存最大与最小的数，然后每次迭代记录最大和最小数
func maxProduct(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	if len(nums) == 1 {
		return nums[0]
	}
	ret, maxVal, minVal := nums[0], nums[0], nums[0]
	for i := 1; i < len(nums); i++ {
		// 更新当前值
		tmpMax, tmpMin := maxVal*nums[i], minVal*nums[i]
		// 更新最大最小值，由于正负数的存在都有三个可能
		maxVal = max(max(tmpMax, tmpMin), nums[i])
		minVal = min(min(tmpMax, tmpMin), nums[i])
		ret = max(ret, maxVal)
	}
	return ret
}

// 160. 相交链表
func getIntersectionNode(headA, headB *ListNode) *ListNode {
	if headA == nil || headB == nil {
		return nil
	}
	tmpA, tmpB := headA, headB
	var lenA, lenB int
	for tmpA != nil {
		lenA++
		tmpA = tmpA.Next
	}
	for tmpB != nil {
		lenB++
		tmpB = tmpB.Next
	}
	if lenA > lenB {
		for cnt := lenA - lenB; cnt > 0; cnt-- {
			headA = headA.Next
		}
	} else if lenB > lenA {
		for cnt := lenB - lenA; cnt > 0; cnt-- {
			headB = headB.Next
		}
	}
	for headA != nil && headB != nil {
		if headA == headB {
			return headA
		}
		headA = headA.Next
		headB = headB.Next
	}
	return nil
}

type MinStack struct {
	stack    []int
	minStack []int
}

func MinStackConstructor() MinStack {
	return MinStack{
		stack:    []int{},
		minStack: []int{math.MaxInt64},
	}
}

func (this *MinStack) Push(x int) {
	this.stack = append(this.stack, x)
	top := this.minStack[len(this.minStack)-1]
	this.minStack = append(this.minStack, min(x, top))
}

func (this *MinStack) Pop() {
	this.stack = this.stack[:len(this.stack)-1]
	this.minStack = this.minStack[:len(this.minStack)-1]
}

func (this *MinStack) Top() int {
	return this.stack[len(this.stack)-1]
}

func (this *MinStack) GetMin() int {
	return this.minStack[len(this.minStack)-1]
}

// 169. 多数元素
// 时间复杂度为 O(n)、空间复杂度为 O(1)
func majorityElement(nums []int) int {
	if len(nums) == 0 {
		return 0
	}
	num, times := nums[0], 1
	for i, v := range nums {
		if i < 1 {
			continue
		}
		if v != num && times > 0 {
			times--
		} else {
			times++
			num = v
		}
	}
	return num
}

// 198. 打家劫舍
// 动态规划，dp[i]为包含当前i节点值的最大和，类似于楼梯跳跃，可包含i-2, i-3两种节点
func rob(nums []int) int {
	if len(nums) == 1 {
		return nums[0]
	}
	if len(nums) == 2 {
		return max(nums[0], nums[1])
	}
	dp := make([]int, len(nums))
	dp[0], dp[1] = nums[0], nums[1]
	ret := max(dp[0], dp[1])
	for i := 2; i < len(nums); i++ {
		if i > 2 {
			dp[i] = max(dp[i-2]+nums[i], dp[i-3]+nums[i])
		} else {
			dp[i] = dp[i-2] + nums[i]
		}
		ret = max(ret, dp[i])
	}
	return ret
}

// 200. 岛屿数量
// dfs
func numIslands(grid [][]byte) int {
	if len(grid) == 0 || len(grid[0]) == 0 {
		return 0
	}
	visit := make([][]bool, len(grid))
	for i := 0; i < len(grid); i++ {
		visit[i] = make([]bool, len(grid[0]))
	}
	// 遍历矩阵
	var dfs func(i, j int)
	dfs = func(i, j int) {
		visit[i][j] = true
		// 上下左右
		if i > 0 && grid[i-1][j] == '1' && !visit[i-1][j] {
			dfs(i-1, j)
		}
		if i < len(grid)-1 && grid[i+1][j] == '1' && !visit[i+1][j] {
			dfs(i+1, j)
		}
		if j > 0 && grid[i][j-1] == '1' && !visit[i][j-1] {
			dfs(i, j-1)
		}
		if j < len(grid[0])-1 && grid[i][j+1] == '1' && !visit[i][j+1] {
			dfs(i, j+1)
		}
	}
	var cnt int
	for i := 0; i < len(grid); i++ {
		for j := 0; j < len(grid[0]); j++ {
			if grid[i][j] == '1' && !visit[i][j] {
				cnt++
				dfs(i, j)
			}
		}
	}
	return cnt
}

// 226. 翻转二叉树
func invertTree(root *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}
	invertTree(root.Left)
	invertTree(root.Right)
	tmp := root.Left
	root.Left = root.Right
	root.Right = tmp
	return root
}

// 215. 数组中的第K个最大元素
// 快排方案或者堆排序
func findKthLargest(nums []int, k int) int {
	rand.Seed(time.Now().UnixNano())
	return partition(nums, 0, len(nums)-1, k)
}

func partition(data []int, left, right, index int) int {
	for left < right {
		pivot := rand.Int()%(right-left) + left
		data[pivot], data[right] = data[right], data[pivot]
		storeIndex := left
		for i := left; i < right; i++ {
			if data[i] < data[right] {
				data[storeIndex], data[i] = data[i], data[storeIndex]
				storeIndex++
			}
		}
		data[storeIndex], data[right] = data[right], data[storeIndex]
		if storeIndex == len(data)-index {
			return data[storeIndex]
		} else if storeIndex < len(data)-index {
			left = storeIndex + 1
		} else {
			right = storeIndex - 1
		}
	}
	return data[left]
}

// 236. 二叉树的最近公共祖先
func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	if root == nil || root == p || root == q {
		return root
	}
	left := lowestCommonAncestor(root.Left, p, q)
	right := lowestCommonAncestor(root.Right, p, q)
	if left != nil && right != nil {
		return root
	}
	if left != nil {
		return left
	}
	return right
}

// 238. 除自身以外数组的乘积
func productExceptSelf(nums []int) []int {
	if len(nums) == 0 || len(nums) == 1 {
		return nil
	}
	// init
	ret := make([]int, len(nums))
	for i := range ret {
		ret[i] = 1
	}
	// cal from left, except first
	for i := 1; i < len(nums); i++ {
		ret[i] = ret[i-1] * nums[i-1]
	}
	// cal from right
	right := 1
	for i := len(nums) - 1; i >= 0; i-- {
		ret[i] = ret[i] * right
		right = right * nums[i]
	}
	return ret
}

// 357. 统计各位数字都不同的数字个数
func countNumbersWithUniqueDigits(n int) int {
	if n == 0 {
		return 1
	}
	if n == 1 {
		return 10
	}
	// i 代表当前有多少位数字
	total, cur := 10, 9
	for i := 2; i <= n; i++ {
		cur = cur * (11 - i)
		total += cur
	}
	return total
}

// 367. 有效的完全平方数
func isPerfectSquare(num int) bool {
	left, right := 0, num
	for left <= right {
		mid := left + (right-left)/2
		val := mid * mid
		if val < num {
			left = mid + 1
		} else if val > num {
			right = mid - 1
		} else {
			return true
		}
	}
	return false
}

// 88. 合并两个有序数组
func mergeSortedArray(nums1 []int, m int, nums2 []int, n int) {
	idx, i, j := len(nums1)-1, m-1, n-1
	for i >= 0 && j >= 0 {
		if nums1[i] > nums2[j] {
			nums1[idx] = nums1[i]
			i--
		} else {
			nums1[idx] = nums2[j]
			j--
		}
		idx--
	}
	// if nums1 left
	for ; i >= 0; i-- {
		nums1[idx] = nums1[i]
		idx--
	}
	// if nums2 left
	for ; j >= 0; j-- {
		nums1[idx] = nums2[j]
		idx--
	}
}

// 27. 移除元素
func removeElement(nums []int, val int) int {
	idx := 0
	for _, v := range nums {
		if v != val {
			nums[idx] = v
			idx++
		}
	}
	return idx
}

// 26. 删除有序数组中的重复项
// 80. 删除有序数组中的重复项 II
func removeDuplicates(nums []int) int {
	duplicatedCnt := 2
	if len(nums) <= 1 {
		return len(nums)
	}
	slow := 0
	for fast, v := range nums {
		if fast < duplicatedCnt || v != nums[slow-duplicatedCnt] {
			nums[slow] = v
			slow++
		}
	}
	return slow
}

// 189. 轮转数组
func rotateArray(nums []int, k int) {
	rotateHandler := func(array []int) {
		arrayLen := len(array)
		for i := 0; i < arrayLen/2; i++ {
			array[arrayLen-1-i], array[i] = array[i], array[arrayLen-1-i]
		}
	}
	rotateHandler(nums)
	rotateHandler(nums[0 : k%len(nums)])
	rotateHandler(nums[k%len(nums):])
}

// 70. 爬楼梯
func climbStairs(n int) int {
	if n == 1 {
		return 1
	}
	if n == 2 {
		return 2
	}
	pre, cur := 1, 2
	for i := 3; i <= n; i++ {
		newCur := pre + cur
		pre, cur = cur, newCur
	}
	return cur
}

// 134. 加油站
func canCompleteCircuit(gas []int, cost []int) int {
	var total, sum int
	start := 0
	for i := 0; i < len(gas); i++ {
		total += gas[i] - cost[i]
		sum += gas[i] - cost[i]
		if sum < 0 {
			sum = 0
			start = i + 1
		}
	}
	if total < 0 {
		return -1
	}
	return start
}

// 918. 环形子数组的最大和
func maxSubarraySumCircular(nums []int) int {
	var newdata = make([]int, len(nums)*2)
	copy(newdata, nums)
	copy(newdata[len(nums):], nums)
	maxSum, curSum := math.MinInt, 0
	var start = 0
	for i, v := range newdata {
		if start >= len(nums) {
			break
		}
		curSum += v
		if i >= len(nums) && i-len(nums) >= start {
			curSum -= v
			start += 1
		}
		maxSum = max(maxSum, curSum)
		if curSum < 0 {
			curSum = 0
			start = i + 1
		}
	}
	return maxSum
}

// 125. 验证回文串
func isPalindrome(s string) bool {
	convertFunc := func(b rune) rune {
		distance := 'a' - 'A'
		if b >= '0' && b <= '9' {
			return b
		}
		if b >= 'A' && b <= 'Z' {
			return b + distance
		}
		if b >= 'a' && b <= 'z' {
			return b
		}
		return 0
	}
	var sb strings.Builder
	for _, v := range s {
		b := convertFunc(v)
		if b != 0 {
			sb.WriteRune(b)
		}
	}
	ret := sb.String()
	for i := 0; i < len(ret)/2; i++ {
		if ret[i] != ret[len(ret)-1-i] {
			return false
		}
	}
	return true
}

// 392. 判断子序列
func isSubsequence(s string, t string) bool {
	var j int
	for i := 0; i < len(s); i++ {
		var find bool
		for j < len(t) {
			if s[i] == t[j] {
				find = true
				j++
				break
			}
			j++
		}
		if !find {
			return false
		}
	}
	return true
}

// 167. 两数之和 II - 输入有序数组
func twoSum(numbers []int, target int) []int {
	index1, index2 := 0, len(numbers)-1
	for index1 < index2 {
		sum := numbers[index1] + numbers[index2]
		if sum == target {
			return []int{index1 + 1, index2 + 1}
		} else if sum < target {
			index1++
		} else {
			index2--
		}
	}
	return nil
}

// 42. 接雨水
func trap(height []int) int {
	if len(height) == 1 {
		return 0
	}
	// 先计算右侧最大
	right := make([]int, len(height))
	right[len(height)-1] = 0
	for j := len(height) - 2; j >= 0; j-- {
		right[j] = max(right[j+1], height[j+1])
	}
	// 再计算左侧最大
	left := make([]int, len(height))
	left[0] = 0
	for j := 1; j < len(height); j++ {
		left[j] = max(left[j-1], height[j-1])
	}
	// 最后计算面积
	var sum int
	for j := 0; j < len(height); j++ {
		if left[j] > height[j] && right[j] > height[j] {
			sum += min(left[j], right[j]) - height[j]
		}
	}
	return sum
}

// 151. 反转字符串中的单词
func reverseWords(s string) string {
	reverseFunc := func(s string) string {
		var sb strings.Builder
		for i := 0; i < len(s); i++ {
			sb.WriteByte(s[len(s)-1-i])
		}
		return sb.String()
	}
	if s == "" {
		return ""
	}
	var sb strings.Builder
	// 移除多余的空格
	sb.WriteByte(s[0])
	for i := 1; i < len(s); i++ {
		if s[i] != ' ' || s[i] != s[i-1] {
			sb.WriteByte(s[i])
		}
	}
	// 移除首位的空格
	str1 := sb.String()
	str2 := strings.TrimSpace(str1)
	// 反转整个串
	reverseTotal := reverseFunc(str2)
	// 反转单个串
	var sbRet strings.Builder
	var start int
	for i := 0; i < len(reverseTotal); i++ {
		if reverseTotal[i] == ' ' {
			// 反转[start,i)区间
			sbRet.WriteString(reverseFunc(reverseTotal[start:i]))
			sbRet.WriteByte(' ')
			start = i + 1
		}
	}
	sbRet.WriteString(reverseFunc(reverseTotal[start:]))
	return sbRet.String()
}

// 14. 最长公共前缀
func longestCommonPrefix(strs []string) string {
	if len(strs) == 0 {
		return ""
	}
	checkStrSize := func(idx int) bool {
		for _, v := range strs {
			if len(v) < idx+1 {
				return false
			}
			if v[idx] != strs[0][idx] {
				return false
			}
		}
		return true
	}
	for i := 0; i < 200; i++ {
		if !checkStrSize(i) {
			return strs[0][:i]
		}
	}
	return ""
}

// 58. 最后一个单词的长度
func lengthOfLastWord(s string) int {
	// 找最后一个单词的起点
	var endPos, endStart = -1, -1
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] != ' ' {
			endPos = i
			break
		}
	}
	// 找到空格
	for i := endPos - 1; i >= 0; i-- {
		if s[i] == ' ' {
			endStart = i
			break
		}
	}
	return endPos - endStart
}

// 209. 长度最小的子数组
func minSubArrayLen(target int, nums []int) int {
	return 0
}

func main() {
	rotate([][]int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}})
}
