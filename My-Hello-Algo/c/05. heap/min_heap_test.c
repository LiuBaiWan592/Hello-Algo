/**
 * @FileName    :min_heap_test.c
 * @Date        :2024-09-06 11:37:02
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :最小堆测试程序
 * @Description :
 */



#include "min_heap.c"

/* Driver Code */
int main() {
    /* 初始化堆 */
    // 初始化小顶堆
    int nums[] = {9, 8, 6, 6, 7, 5, 2, 1, 4, 3, 6, 2};
    MinHeap *minHeap = newMinHeap(nums, sizeof(nums) / sizeof(int));
    printf("输入数组并建堆后\n");
    printHeap(minHeap->data, minHeap->size);

    /* 获取堆顶元素 */
    printf("\n堆顶元素为 %d\n", peek(minHeap));

    /* 元素入堆 */
    push(minHeap, 7);
    printf("\n元素 7 入堆后\n");
    printHeap(minHeap->data, minHeap->size);

    /* 堆顶元素出堆 */
    int top = pop(minHeap);
    printf("\n堆顶元素 %d 出堆后\n", top);
    printHeap(minHeap->data, minHeap->size);

    /* 获取堆大小 */
    printf("\n堆元素数量为 %d\n", size(minHeap));

    /* 判断堆是否为空 */
    printf("\n堆是否为空 %d\n", isEmpty(minHeap));

    // 释放内存
    delMinHeap(minHeap);

    return 0;
}
