/**
 * @FileName    :binary_tree_bfs.c
 * @Date        :2024-09-01 11:49:34
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :二叉树遍历-层序遍历（广度优先搜索BFS）
 * @Description :借助队列实现，队列用于存储自上而下自左而右的二叉树节点，这样队列中的节点顺序就为层序遍历的顺序
 *               每访问队列中的一个节点，将节点的值保存到层序遍历结果序列中返回即可，同时返回节点个数
 */

#include "../utils/common.h"

#define MAX_SIZE 100

/* 层序遍历 */
int *levelOrder(TreeNode *root, int *size) {
    /* 辅助队列 */
    int front, rear;
    TreeNode **queue;
    /* 辅助数组 */
    int index, *arr;
    TreeNode *node;

    /* 初始化辅助队列 */
    queue = malloc(sizeof(TreeNode) * MAX_SIZE);
    front = 0, rear = 0;
    // 加入根节点
    queue[rear++] = root;

    // 初始化一个列表，用于保存遍历序列
    /* 初始化辅助数组 */
    arr = malloc(sizeof(int) * MAX_SIZE);
    index = 0;

    while (front < rear) {
        // 队列出队
        node = queue[front++];
        // 保存节点值
        arr[index++] = node->val;
        // 左子节点入队
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        // 右子节点入队
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }

    // 更新数组长度的值，刨除初始化时的空值
    *size = index;
    arr = realloc(arr, sizeof(int) * index);

    // 释放辅助队列数组空间
    free(queue);
    return arr;
}

/* Driver Code*/
int main() {
    /* 初始化二叉树 */
    // 借助数组直接生成二叉树的函数arrayToTree()
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(nums) / sizeof(int);
    TreeNode *root = arrayToTree(nums, size);
    printf("初始化二叉树为\n");
    printTree(root);

    /* 层序遍历 */
    // 需要传入数组的长度
    int *arr = levelOrder(root, &size);
    printf("层序遍历的节点序列为 = ");
    printArray(arr, size);

    // 释放内存
    freeMemoryTree(root);
    free(arr);
    return 0;
}