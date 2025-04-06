/**
 * @FileName    :max_heap_test.c
 * @Date        :2024-09-05 15:02:58
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :最大堆测试程序
 * @Description :
 */



#include "max_heap.c"

/* Driver Code */
int main() {
    /* 初始化堆 */
    // 初始化大顶堆
    int nums[] = {9, 8, 6, 6, 7, 5, 2, 1, 4, 3, 6, 2};
    MaxHeap *maxHeap = newMaxHeap(nums, sizeof(nums) / sizeof(int));
    printf("输入数组并建堆后\n");
    printHeap(maxHeap->data, maxHeap->size);

    /* 获取堆顶元素 */
    printf("\n堆顶元素为 %d\n", peek(maxHeap));

    /* 元素入堆 */
    push(maxHeap, 7);
    printf("\n元素 7 入堆后\n");
    printHeap(maxHeap->data, maxHeap->size);

    /* 堆顶元素出堆 */
    int top = pop(maxHeap);
    printf("\n堆顶元素 %d 出堆后\n", top);
    printHeap(maxHeap->data, maxHeap->size);

    /* 获取堆大小 */
    printf("\n堆元素数量为 %d\n", size(maxHeap));

    /* 判断堆是否为空 */
    printf("\n堆是否为空 %d\n", isEmpty(maxHeap));

    // 释放内存
    delMaxHeap(maxHeap);

    return 0;
}
