/**
 * @FileName    :common_test.c
 * @Date        :2025-03-01 18:37:24
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :通用头文件测试
 * @Description :测试通用头文件中的链表和树相关函数
 */

#include "../utils/common.h"

void testListNode() {
    int nums[] = {2, 3, 5, 6, 7};
    int size = sizeof(nums) / sizeof(int);
    ListNode *head = arrToLinkedList(nums, size);
    printLinkedList(head);
}

void testTreeNode() {
    int nums[] = {1, 2, 3, INT_MAX, 5, 6, INT_MAX};
    int size = sizeof(nums) / sizeof(int);
    TreeNode *root = arrayToTree(nums, size);

    // print tree
    printTree(root);

    // tree to arr
    int *arr = treeToArray(root, &size);
    printArray(arr, size);
}

int main(int argc, char *argv[]) {
    printf("==testListNode==\n");
    testListNode();
    printf("==testTreeNode==\n");
    testTreeNode();
    return 0;
}
