/**
 * @FileName    :print_util.h
 * @Date        :2025-03-01 17:04:14
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :打印输出函数工具
 * @Description :打印整形数组、打印浮点型数组、打印链表、打印二叉树、打印堆
 */

#ifndef PRINT_UTIL_H
#define PRINT_UTIL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list_node.h"
#include "tree_node.h"

#ifdef __cplusplus
extern "C" {
#endif

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

/* 打印数组 */
void printArrayFloat(float arr[], int size) {
    if (arr == NULL || size == 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%.2f, ", arr[i]);
    }
    printf("%.2f]\n", arr[size - 1]);
}

/* 打印链表 */
void printLinkedList(ListNode *node) {
    if (node == NULL) {
        return;
    }
    while (node->next != NULL) {
        printf("%d -> ", node->val);
        node = node->next;
    }
    printf("%d\n", node->val);
}

typedef struct Trunk {
    struct Trunk *prev;
    char *str;
} Trunk;

Trunk *newTrunk(Trunk *prev, char *str) {
    Trunk *trunk = (Trunk *)malloc(sizeof(Trunk));
    trunk->prev = prev;
    trunk->str = (char *)malloc(sizeof(char) * 10);
    strcpy(trunk->str, str);
    return trunk;
}

void showTrunks(Trunk *trunk) {
    if (trunk == NULL) {
        return;
    }
    showTrunks(trunk->prev);
    printf("%s", trunk->str);
}

/**
 * 打印二叉树
 * This tree printer is borrowed from TECHIE DELIGHT
 * https://www.techiedelight.com/c-program-print-binary-tree/
 */
void printTreeHelper(TreeNode *node, Trunk *prev, bool isRight) {
    if (node == NULL) {
        return;
    }
    char *prev_str = "    ";
    Trunk *trunk = newTrunk(prev, prev_str);
    printTreeHelper(node->right, trunk, true);
    if (prev == NULL) {
        trunk->str = "———";
    } else if (isRight) {
        trunk->str = "/———";
        prev_str = "   |";
    } else {
        trunk->str = "\\———";
        prev->str = prev_str;
    }
    showTrunks(trunk);
    printf("%d\n", node->val);

    if (prev != NULL) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTreeHelper(node->left, trunk, false);
}

/* 打印二叉树 */
void printTree(TreeNode *root) {
    printTreeHelper(root, NULL, false);
}

/* 打印堆 */
void printHeap(int arr[], int size) {
    TreeNode *root;
    printf("堆的数组表示：");
    printArray(arr, size);
    printf("堆的树状表示：\n");
    root = arrayToTree(arr, size);
    printTree(root);
}

#ifdef __cplusplus
}
#endif

#endif // PRINT_UTIL_H
