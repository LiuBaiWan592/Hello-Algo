/**
 * @FileName    :selection_sort.c
 * @Date        :2024-09-17 19:02:21
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :选择排序（selection sort）
 * @Description :开启一个循环，每轮从未排序区间选择最小的元素，将其放到已排序区间的末尾。
 */

#include "../utils/common.h"

/* 选择排序 */
void selectionSort(int *nums, int n) {
    // 外循环：未排序区间为 [i, n-1]
    for (int i = 0; i < n - 1; i++) {
        // 用 k 来记录未排序区间的最小元素
        int k = i;
        // 内循环：找到未排序区间内的最小元素
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[k]) {
                k = j; // 记录最小元素的索引
            }
        }
        // 将该最小元素与未排序区间的首个元素交换
        int tmp = nums[i];
        nums[i] = nums[k];
        nums[k] = tmp;
    }
}

/* Driver Code */
int main() {
    int nums[] = {4, 1, 3, 1, 5, 2};
    int n = sizeof(nums) / sizeof(nums[0]);

    selectionSort(nums, n);

    printf("选择排序完成后 nums = ");
    printArray(nums, n);

    return 0;
}
