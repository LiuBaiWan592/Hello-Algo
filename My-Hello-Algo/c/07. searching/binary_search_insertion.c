/**
 * @FileName    :binary_search_insertion.c
 * @Date        :2024-09-13 14:32:22
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :二分查找插入点（搜索目标元素的插入位置）
 * @Description :一、无重复元素（待插入的有序数组不存在重复元素）的情况：
 *               1. 当数组中包含 target 时，将 target 插入到相等元素的左边，这意味着新插入的 target 替换了原来 target 的位置。
 *               也就是说，当数组包含 target 时，插入点的索引就是该 target 的索引。
 *               2. 当数组中不存在 target 时，当 nums[m] < target 时 i 移动，这意味着指针 i 在向大于等于 target 的元素靠近。
 *               同理，指针 j 始终在向小于等于 target 的元素靠近。
 *               二分结束时一定有：i 指向首个大于 target 的元素、 j 指向首个小于 target 的元素。
 *               易得当数组不包含 target 时，插入索引为 i 。
 *
 *               二、存在重复元素的情况：
 *               将目标元素插入到最左边，所以我们需要查找数组中最左一个 target 的索引
 *               方法一：时间复杂度为 O(n) 。当数组中存在很多重复的 target 时，该方法效率很低。
 *                      1. 执行二分查找，得到任意一个 target 的索引，记为 k 。
 *                      2. 从索引 k 开始，向左进行线性遍历，当找到最左边的 target 时返回。
 *               方法二：拓展二分查找代码，整体流程保持不变，每轮先计算中点索引 m ，再判断 target 和 nums[m] 的大小关系
 *                      1. 当 nums[m] < target 或 nums[m] > target 时，说明还没有找到 target ，
 *                         因此采用普通二分查找的缩小区间操作，从而使指针 i 和 j 向 target 靠近。
 *                      2. 当 nums[m] == target 时，说明小于 target 的元素在区间 [i, m -1] 中，
 *                         因此采用 j = m - 1 来缩小区间，从而使指针 j 向小于 target 的元素靠近。
 *                      循环完成后，i 指向最左边的 target ，j 指向首个小于 target 的元素，因此索引 i 就是插入点。
 */

#include "../utils/common.h"

/* 二分查找插入点（无重复元素） */
int binarySearchInsertionSimple(int *nums, int len, int target) {
    // 初始化双闭区间 [0, n-1]
    int i = 0, j = len - 1;
    while (i <= j) {
        int m = i + (j - i) / 2; // 计算中点索引 m
        // target 在区间 [m+1, j] 中
        if (nums[m] < target) {
            i = m + 1;
        }
        // target 在区间 [i, m-1] 中
        else if (nums[m] > target) {
            j = m - 1;
        }
        // 找到 target ，返回插入点 m
        else {
            return m;
        }
    }
    return i;
}

/* 二分查找插入点（存在重复元素） */
int binarySearchInsertion(int *nums, int len, int target) {
    // 初始化双闭区间[0, n - 1]
    int i = 0, j = len - 1;
    while (i <= j) {
        int m = i + (j - i) / 2; // 计算中点索引 m
        // target 在区间 [m+1, j] 中
        if (nums[m] < target) {
            i = m + 1;
        }
        // target 在区间 [i, m-1] 中
        else if (nums[m] > target) {
            j = m - 1;
        }
        // 找到 target ，首个小于 target 的元素在区间 [i, m-1] 中,采用 j = m - 1 来缩小区间
        else {
            j = m - 1;
        }
    }
    // 返回插入点 i
    return i;
}

/* Driver Code */
int main() {
    // 无重复元素的数组
    int nums1[] = {1, 3, 6, 8, 12, 15, 23, 26, 31, 35};
    printf("\n数组 nums = ");
    printArray(nums1, sizeof(nums1) / sizeof(nums1[0]));
    // 二分查找插入点
    int targets1[] = {6, 9};
    for (int i = 0; i < sizeof(targets1) / sizeof(targets1[0]); i++) {
        int index = binarySearchInsertionSimple(nums1, sizeof(nums1) / sizeof(nums1[0]), targets1[i]);
        printf("元素 %d 的插入点的索引为 %d\n", targets1[i], index);
    }

    // 包含重复元素的数组
    int nums2[] = {1, 3, 6, 6, 6, 6, 6, 10, 12, 15};
    printf("\n数组 nums = ");
    printArray(nums2, sizeof(nums2) / sizeof(nums2[0]));
    // 二分查找插入点
    int targets2[] = {2, 6, 20};
    for (int i = 0; i < sizeof(targets2) / sizeof(int); i++) {
        int index = binarySearchInsertion(nums2, sizeof(nums2) / sizeof(nums2[0]), targets2[i]);
        printf("元素 %d 的插入点的索引为 %d\n", targets2[i], index);
    }

    return 0;
}
