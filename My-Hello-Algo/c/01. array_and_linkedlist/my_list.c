/**
 * @FileName    :my_list.c
 * @Date        :2024-08-22 10:23:22
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :列表（动态数组）的基本操作
 * @Description :简易版列表，包括以下三个重点设计。
                 初始容量：选取一个合理的数组初始容量。在本示例中，我们选择 10 作为初始容量。
                 数量记录：声明一个变量 size ，用于记录列表当前元素数量，并随着元素插入和删除实时更新。
                          根据此变量，我们可以定位列表尾部，以及判断是否需要扩容。
                 扩容机制：若插入元素时列表容量已满，则需要进行扩容。先根据扩容倍数创建一个更大的数组，
                          再将当前数组的所有元素依次移动至新数组。在本示例中，我们规定每次将数组扩容至之前的 2 倍。
 */

#include <stdio.h>
#include <stdlib.h>

/* 列表类 */
typedef struct list {
    int *arr;        // 数组（存储列表元素）
    int capacity;    // 列表容量
    int size;        // 列表大小
    int extendRatio; // 列表每次扩容的倍数
} MyList;

/* 构造函数 */
MyList *newMyList() {
    MyList *nums = (MyList *)malloc(sizeof(MyList));
    nums->capacity = 10;
    nums->arr = (int *)malloc(sizeof(int) * nums->capacity);
    nums->size = 0;
    nums->extendRatio = 2;
}

/* 析构函数 */
void delMyList(MyList *nums) {
    free(nums->arr);
    free(nums);
}

void extendCapacity(MyList *nums);

/* 获取列表长度 */
int size(MyList *nums) {
    return nums->size;
}

/* 获取列表容量 */
int capacity(MyList *nums) {
    return nums->capacity;
}

/* 访问元素 */
int get(MyList *nums, int index) {
    if (index >= 0 && index < nums->size) // 越界检查
    {
        return nums->arr[index];
    } else {
        printf("index越界");
        return -1;
    }
}

/* 更新元素 */
void set(MyList *nums, int index, int num) {
    if (index >= 0 && index < nums->size) // 越界检查
    {
        nums->arr[index] = num;
    } else {
        printf("index越界");
    }
}

/* 在尾部添加元素 O(1) 扩容时O(n) */
void add(MyList *nums, int num) {
    if (size(nums) == capacity(nums)) // 容量检查
    {
        extendCapacity(nums);
        printf("扩容");
    }
    nums->arr[size(nums)] = num;
    nums->size++;
}

/* 在中间插入元素 O(n) */
void insert(MyList *nums, int index, int num) {
    if (index >= 0 && index < nums->size) // 越界检查
    {
        if (size(nums) == capacity(nums)) // 容量检查
        {
            extendCapacity(nums);
            printf("扩容");
        }
        for (int i = size(nums); i > index; i--) // 数组元素插入方法，从后往前一次后移
        {
            nums->arr[i] = nums->arr[i - 1];
        }
        nums->arr[index] = num;
        nums->size++;
    } else {
        printf("index越界");
    }
}

/* 删除元素 O(n) */
int removeItem(MyList *nums, int index) {
    if (index >= 0 && index < nums->size) // 越界检查
    {
        int num = nums->arr[index];
        for (int i = index; i < size(nums) - 1; i++) {
            nums->arr[i] = nums->arr[i + 1];
        }
        nums->size--;
        return num;
    } else {
        printf("index越界");
        return -65535;
    }
}

/* 列表扩容 O(n) */
void extendCapacity(MyList *nums) { // 先分配空间
    int newCapacity = capacity(nums) * nums->extendRatio;
    int *newArray = (int *)malloc(sizeof(int) * newCapacity);
    int *oldArray = nums->arr;

    // 拷贝旧数据到新数据
    for (int i = 0; i < size(nums); i++) {
        newArray[i] = oldArray[i];
    }

    // 释放旧数据
    free(oldArray);

    // 更新新数据
    nums->arr = newArray;
    nums->capacity = newCapacity;
}

/* 将列表转换为 Array 用于打印 */
int *toArray(MyList *nums) {
    return nums->arr;
}

/* 打印数组 */
void printArray(int arr[], int size) {
    if (arr == NULL || size == 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size - 1]);
}

int main() {
    /* 初始化列表 */
    MyList *nums = newMyList();
    /* 在尾部添加元素 */
    add(nums, 1);
    add(nums, 3);
    add(nums, 2);
    add(nums, 5);
    add(nums, 4);
    printf("列表 nums = ");
    printArray(toArray(nums), size(nums));
    printf("容量 = %d ，长度 = %d\n", capacity(nums), size(nums));

    /* 在中间插入元素 */
    insert(nums, 3, 6);
    printf("在索引 3 处插入数字 6 ，得到 nums = ");
    printArray(toArray(nums), size(nums));

    /* 删除元素 */
    removeItem(nums, 3);
    printf("删除索引 3 处的元素，得到 nums = ");
    printArray(toArray(nums), size(nums));

    /* 访问元素 */
    int num = get(nums, 1);
    printf("访问索引 1 处的元素，得到 num = %d\n", num);

    /* 更新元素 */
    set(nums, 1, 0);
    printf("将索引 1 处的元素更新为 0 ，得到 nums = ");
    printArray(toArray(nums), size(nums));

    /* 测试扩容机制 */
    for (int i = 0; i < 10; i++) {
        // 在 i = 5 时，列表长度将超出列表容量，此时触发扩容机制
        add(nums, i);
    }

    printf("扩容后的列表 nums = ");
    printArray(toArray(nums), size(nums));
    printf("容量 = %d ，长度 = %d\n", capacity(nums), size(nums));

    /* 释放分配内存 */
    delMyList(nums);

    return 0;
}