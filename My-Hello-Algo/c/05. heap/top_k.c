/**
 * @FileName    :top-k.c
 * @Date        :2024-09-06 11:35:53
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :Top-k 问题：给定一个长度为 n 的无序数组 nums ，请返回数组中最大的 k 个元素。
 * @Description :基于堆更加高效地解决 Top-k 问题：
 *               1. 初始化一个小顶堆，其堆顶元素最小。
 *               2. 先将数组前 k 个元素依次入堆。
 *               3. 从第 k + 1 个元素开始，若当前元素大于堆顶元素，则将堆顶元素出堆，当前元素入堆。
 *               4. 遍历完成后，堆中保存的就是最大的k个元素。
 */

#include "min_heap.c"

/* 取出堆中元素 */
int *getMinHeap(MinHeap *minHeap) {
    // 将堆中所有元素存入 res 数组
    int *res = malloc(sizeof(int) * minHeap->size);
    // for (int i = 0; i < minHeap->size; i++)
    // {
    //     res[i] = minHeap->data[i];
    // }
    //
    memcpy(res, minHeap->data, minHeap->size * sizeof(int));
    return res;
}

// 基于堆查找数组中最大的 k 个元素的函数
int *topKHeap(int *nums, int numsSize, int k) {
    // 初始化小顶堆
    // 完全实现小顶堆，不采用大顶堆取反操作
    // 初始化时，直接将数组的前 k 个元素入堆
    MinHeap *minHeap = newMinHeap(nums, k);
    // 从第 k+1 个元素开始，保持堆的长度为 k
    for (int i = k; i < numsSize; i++) {
        // 若当前元素大于堆顶元素，则将堆顶元素出堆、当前元素入堆
        if (nums[i] > peek(minHeap)) {
            pop(minHeap);
            push(minHeap, nums[i]);
        }
    }
    int *res = getMinHeap(minHeap);
    // 释放内存
    free(minHeap);
    return res;
}

/* Driver Code */
int main() {
    int nums[] = {1, 7, 6, 3, 2};
    int k = 3;
    int sizeNums = sizeof(nums) / sizeof(nums[0]);

    int *res = topKHeap(nums, sizeNums, k);
    printf("最大的 %d 个元素为: ", k);
    printArray(res, k);

    free(res);
    return 0;
}
