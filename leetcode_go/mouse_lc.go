package main

import (
	"math"
	"sort"
	"strconv"
	"strings"
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

func max(num1, num2 int) int {
	if num1 > num2 {
		return num1
	}
	return num2
}

func min(num1, num2 int) int {
	if num1 < num2 {
		return num1
	}
	return num2
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
	// data[i][j]标识是否回文
	// 边界case，j=i+1和i=j
	sLen := len(s)
	if sLen == 0 {
		return ""
	}
	data := make([][]bool, sLen)
	for i := 0; i < sLen; i++ {
		data[i] = make([]bool, sLen)
	}
	// dp
	ret := string(s[0])
	for i := sLen - 1; i >= 0; i-- {
		for j := i; j < sLen; j++ {
			if i == j {
				data[i][j] = true
			} else if j == i+1 && s[i] == s[j] {
				data[i][j] = true
				if len(ret) < 2 {
					ret = s[i : j+1]
				}
			} else if s[i] == s[j] && data[i+1][j-1] {
				data[i][j] = true
				if len(ret) < (j - i + 1) {
					ret = s[i : j+1]
				}
			}
		}
	}
	return ret
}

// 11. Container With Most Water
// Input: [1,8,6,2,5,4,8,3,7]
// Output: 49
func maxArea(height []int) int {
	area, left, right := 0, 0, len(height)-1
	for left < right {
		var high int
		width := right - left
		if height[left] < height[right] {
			high = height[left]
			left++
		} else {
			high = height[right]
			right--
		}
		tmp := width * high
		if tmp > area {
			area = tmp
		}
	}
	return area
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
//  [-1, 0, 1],
//  [-1, -1, 2]
// ]
func threeSum(nums []int) [][]int {
	var ret [][]int
	sort.Ints(nums)
	for i := 0; i < len(nums); i++ {
		// 重复的解直接跳过
		if i > 0 && nums[i] == nums[i-1] {
			continue
		}
		j, k := i+1, len(nums)-1
		for j < k {
			val := nums[i] + nums[j] + nums[k]
			if val == 0 {
				ret = append(ret, []int{nums[i], nums[j], nums[k]})
				j++
				k--
				// 跳过相同元素
				for ; j < k && nums[j] == nums[j-1]; j++ {
				}
			} else if val > 0 {
				k--
			} else {
				j++
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
//  [1, 7],
//  [1, 2, 5],
//  [2, 6],
//  [1, 1, 6]
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
	var mostidx int
	for i, v := range nums {
		if mostidx >= i {
			mostidx = max(i+v, mostidx)
			if mostidx >= len(nums)-1 {
				return true
			}
		}
	}
	return false
}

// 53. 最大子数组和
// 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
// 输出：6
// 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
func maxSubArray(nums []int) int {
	var maxSum, tmpSum = math.MinInt, 0
	for _, v := range nums {
		if tmpSum > 0 {
			tmpSum += v
		} else {
			tmpSum = v
		}
		maxSum = max(tmpSum, maxSum)
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

func main() {
	//l := Constructor(2)
	//l.Put(1, 1)
	//l.Put(2, 2)
	//fmt.Println(l.Get(1))
	//fmt.Println(l.Get(2))
	//l.Put(3, 3)
	//fmt.Println(l.Get(1))
	//fmt.Println(l.Get(3))
	//generate(5)
	// arrayRankTransform([]int{37, 12, 28, 9, 100, 56, 80, 5, 12})
	//fmt.Println(searchRange([]int{1}, 1))
	rotate([][]int{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}})
}
