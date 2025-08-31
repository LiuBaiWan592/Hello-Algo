/**
 * @FileName    :insertion_sort.c
 * @Date        :2024-09-18 16:18:10
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :插入排序（insertion sort）
 * @Description :在未排序区间选择一个基准元素，将该元素与其左侧已排序区间的元素逐一比较大小，并将该元素插入到正确的位置。
 *               1. 初始状态下，数组的第 1 个元素已完成排序。
 *               2. 选取数组的第 2 个元素作为 base ，将其插入到正确位置后，数组的前 2 个元素已排序。
 *               3. 选取第 3 个元素作为 base ，将其插入到正确位置后，数组的前 3 个元素已排序。
 *               4. 以此类推，在最后一轮中，选取最后一个元素作为 base ，将其插入到正确位置后，所有元素均已排序。
 */

#include "../utils/common.h"

/* 插入排序 */
void insertionSort(int *nums, int n) {
    // 外循环：已排序区间为 [0, i-1]
    for (int i = 1; i < n; i++) {
        int base = nums[i], j = i - 1;
        // 内循环：将 base 插入到已排序区间 [0, i-1] 中的正确位置
        while (j >= 0 && nums[j] > base) {
            // 将 nums[j] 向右移动一位
            nums[j + 1] = nums[j];
            j--;
        }
        // 将 base 赋值到正确位置
        nums[j + 1] = base;
    }
}

/* Driver Code */
int main() {
    int nums[] = {4, 1, 3, 1, 5, 2};
    insertionSort(nums, 6);
    printf("插入排序完成后 nums = ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
