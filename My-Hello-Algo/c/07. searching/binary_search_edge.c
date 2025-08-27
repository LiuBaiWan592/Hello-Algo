/**
 * @FileName    :binary_search_edge.c
 * @Date        :2024-09-14 15:50:14
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :二分查找边界
 * @Description :一、查找左边界
 *               给定一个长度为 n 的有序数组 nums ，其中可能包含重复元素。请返回数组中最左一个元素 target 的索引。
 *               若数组中不包含该元素，则返回 -1 。
 *               1. 二分查找插入点的方法，搜索完成后 i 指向最左一个 target ，因此查找插入点本质上是在查找最左一个 target 的索引。
 *               2. 数组中可能不包含 target ，这种情况可能导致以下两种结果。
 *                      插入点的索引 i 越界。
 *                      元素 nums[i] 与 target 不相等。
 *                  当遇到以上两种情况时，直接返回 -1 即可。
 *
 *               二、查找右边界
 *               方法一、直接的方式是修改二分查找插入点的代码，替换在 nums[m] == target 情况下的指针收缩操作
 *                      替换为为 i = m + 1， 返回 j 即为最后一个 <= target 的数的指针。
 *               方法二、复用查找左边界
 *                      利用查找最左元素的函数来查找最右元素，具体方法为：将查找最右一个 target 转化为查找最左一个 target + 1
 *                      查找完成后，指针 i 指向最左一个 target + 1（如果存在），而 j 指向最右一个 target ，因此返回 j 即可
 *               方法三、转化为查找元素
 *                      当数组不包含 target 时，最终 i 和 j 会分别指向首个大于、小于 target 的元素。
 *                      因此，我们可以构造一个数组中不存在的元素，用于查找左右边界。
 *                          查找最左一个 target ：可以转化为查找 target - 0.5 ，并返回指针 i 。
 *                          查找最右一个 target ：可以转化为查找 target + 0.5 ，并返回指针 j 。
 *                      注：target 需要修改成浮点类型（float）
 */

#include "../utils/common.h"

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
            // i = m + 1;
        }
    }
    // 返回插入点 i
    return i;
}

/* 二分查找最左一个 target */
int binarySearchLeftEdge(int *nums, int len, int target) {
    // 等价于查找 target 的插入点
    int i = binarySearchInsertion(nums, len, target);
    // 未找到 target ，返回 -1
    if (i == len || nums[i] != target) {
        return -1;
    }
    // 找到 target ，返回索引 i
    return i;
}

/* 二分查找最右一个 target */
int binarySearchRightEdge(int *nums, int len, int target) {
    // 转化为查找最左一个 target + 1
    int i = binarySearchInsertion(nums, len, target + 1);
    // j 指向最右一个 target ，i 指向首个大于 target 的元素
    int j = i - 1;
    // 未找到 target ，返回 -1
    if (j == -1 || nums[j] != target) {
        return -1;
    }
    return j;
}

/* Driver Code */
int main() {
    // 包含重复元素的数组
    int nums[] = {1, 3, 6, 6, 6, 6, 6, 10, 12, 15};
    printf("\n数组 nums = ");
    printArray(nums, sizeof(nums) / sizeof(nums[0]));

    // 二分查找左边界和右边界
    int targets[] = {6, 7};
    for (int i = 0; i < sizeof(targets) / sizeof(targets[0]); i++) {
        int index = binarySearchLeftEdge(nums, sizeof(nums) / sizeof(nums[0]), targets[i]);
        printf("最左一个元素 %d 的索引为 %d\n", targets[i], index);
        index = binarySearchRightEdge(nums, sizeof(nums) / sizeof(nums[0]), targets[i]);
        printf("最右一个元素 %d 的索引为 %d\n", targets[i], index);
    }

    return 0;
}