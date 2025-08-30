/**
 * @FileName    :bubble_sort.c
 * @Date        :2024-09-17 19:15:22
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :冒泡排序（bubble sort）
 * @Description :通过连续地比较与交换相邻元素实现排序。这个过程就像气泡从底部升到顶部一样，因此得名冒泡排序。
 *               从数组最左端开始向右遍历，依次比较相邻元素大小，如果“左元素 > 右元素”就交换二者。
 *               遍历完成后，最大的元素会被移动到数组的最右端。
 */

#include "../utils/common.h"

/* 冒泡排序 */
void bubbleSort(int *nums, int n) {
    // 外循环：未排序区间为 [0, i]
    for (int i = n - 1; i > 0; i--) {
        // 内循环：将未排序区间 [0, i] 中的最大元素交换至该区间的最右端
        for (int j = 0; j < i; j++) {
            if (nums[j] > nums[j + 1]) {
                int tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}

/* 冒泡排序（标志优化）*/
// 如果某轮“冒泡”中没有执行任何交换操作，说明数组已经完成排序，可直接返回结果。
// 因此，可以增加一个标志位 flag 来监测这种情况，一旦出现就立即返回。
void bubbleSortWithFlag(int *nums, int n) {
    // 外循环：未排序区间为 [0, i]
    for (int i = n - 1; i > 0; i--) {
        bool flag = false;
        // 内循环：将未排序区间 [0, i] 中的最大元素交换至该区间的最右端
        for (int j = 0; j < i; j++) {
            if (nums[j] > nums[j + 1]) {
                int tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
}

/* Driver Code */
int main() {
    int nums[6] = {4, 1, 3, 1, 5, 2};
    printf("冒泡排序后: ");
    bubbleSort(nums, 6);
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums[i]);
    }

    int nums1[6] = {4, 1, 3, 1, 5, 2};
    printf("\n优化版冒泡排序后: ");
    bubbleSortWithFlag(nums1, 6);
    for (int i = 0; i < 6; i++) {
        printf("%d ", nums1[i]);
    }
    printf("\n");

    return 0;
}
