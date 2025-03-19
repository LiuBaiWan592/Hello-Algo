/**
 * @FileName    :binary_tree_dfs.c
 * @Date        :2024-09-02 11:33:07
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :二叉树遍历-前序、中序、后序遍历（深度优先搜索DFS）
 * @Description :基于递归实现深度优先搜索和基于迭代实现深度优先搜索（借助栈）
 */

#include "../utils/common.h"

#define MAX_SIZE 100

// 辅助数组，用于存储遍历结果序列
int result[MAX_SIZE];

/* 递归实现：代码实现较为简单，效率较低 */
/* 前序遍历 */
void preOrder(TreeNode *root, int *size) {
    if (root == NULL) {
        return;
    }
    // 访问优先级：根节点 -> 左子树 -> 右子树
    result[(*size)++] = root->val;
    preOrder(root->left, size);
    preOrder(root->right, size);
}

/* 中序遍历 */
void inOrder(TreeNode *root, int *size) {
    if (root == NULL) {
        return;
    }
    // 访问优先级：左子树 -> 根节点 -> 右子树
    inOrder(root->left, size);
    result[(*size)++] = root->val;
    inOrder(root->right, size);
}

/* 后序遍历 */
void postOrder(TreeNode *root, int *size) {
    if (root == NULL) {
        return;
    }
    // 访问优先级：左子树 -> 右子树 -> 根节点
    postOrder(root->left, size);
    postOrder(root->right, size);
    result[(*size)++] = root->val;
}

/* 迭代实现：借助栈数据结构实现，代码较为复杂 */
/* 前序遍历 */
void preOrderStack(TreeNode *root, int size) {
    if (root == NULL) {
        return;
    }
    TreeNode **stack = malloc(sizeof(TreeNode *) * size);
    TreeNode *node = root;
    int top = -1;
    int index = 0;
    while (top >= 0 || node != NULL) {
        if (node != NULL) {
            result[index++] = node->val;
            stack[++top] = node;
            node = node->left;
        } else {
            node = stack[top--];
            node = node->right;
        }
    }
    /* 方法2 */
    // stack[++top] = node;
    // while (top >= 0)
    // {
    //     node = stack[top--];
    //     result[index++] = node->val;
    //     if (node->right != NULL)
    //     {
    //         stack[++top] = node->right;
    //     }
    //     if (node->left != NULL)
    //     {
    //         stack[++top] = node->left;
    //     }
    // }
}

/* 中序遍历 */
void inOrderStack(TreeNode *root, int size) {
    if (root == NULL) {
        return;
    }
    TreeNode **stack = malloc(sizeof(TreeNode *) * size);
    TreeNode *node = root;
    int top = -1;
    int index = 0;
    /* 方法1 */
    while (top >= 0 || node != NULL) {
        if (node != NULL) {
            stack[++top] = node;
            node = node->left;
        } else {
            node = stack[top--];
            result[index++] = node->val;
            node = node->right;
        }
    }
    //
    //
    /* 方法2 */
    // 1. 压栈的同时，将当前指针移动到最左边的节点。
    // 2. 出栈，获取节点值。
    // 3. 将指针移动到右子节点。循环1-3直到栈为空。
    //
    // while (top >= 0 || node != NULL)
    // {
    //     while (node != NULL)
    //     {
    //         stack[++top] = node;
    //         node = node->left;
    //     }
    //     node = stack[top--];
    //     result[index++] = node->val;
    //     node = node->right;
    // }
}

/* 后序遍历:使用双栈 */
// 栈1用于存储节点，栈2用于存储栈1出栈的节点。栈1出栈的顺序是根右左，栈2出栈的顺序是左右根。
void postOrderStack(TreeNode *root, int size) {
    if (root == NULL) {
        return;
    }
    TreeNode **stack1 = malloc(sizeof(TreeNode *) * size);
    TreeNode **stack2 = malloc(sizeof(TreeNode *) * size);
    TreeNode *node = root;
    int top1 = -1, top2 = -1;
    int index = 0;
    stack1[++top1] = node;
    // 遍历栈1，将节点出栈，存入栈2， 入栈左右子节点。
    while (top1 >= 0) {
        node = stack1[top1--];
        stack2[++top2] = node;
        if (node->left != NULL) {
            stack1[++top1] = node->left;
        }
        if (node->right != NULL) {
            stack1[++top1] = node->right;
        }
    }
    // 遍历栈2，将节点出栈，存入结果数组。
    while (top2 >= 0) {
        result[index++] = stack2[top2--]->val;
    }
}

/* Driver Code */
int main() {
    /* 初始化二叉树 */
    // 这里借助了一个从数组直接生成二叉树的函数
    int nums[] = {1, 2, 3, 4, INT_MAX, 6, 7, 8, 9, INT_MAX, INT_MAX, 12, INT_MAX, INT_MAX, 15};
    int size = sizeof(nums) / sizeof(int);
    TreeNode *root = arrayToTree(nums, size);
    printf("初始化二叉树\n");
    printTree(root);

    /* 前序遍历 */
    // 初始化辅助数组
    size = 0;
    preOrder(root, &size);
    printf("前序遍历的节点打印序列 = ");
    printArray(result, size);

    /* 中序遍历 */
    size = 0;
    inOrder(root, &size);
    printf("中序遍历的节点打印序列 = ");
    printArray(result, size);

    /* 后序遍历 */
    size = 0;
    postOrder(root, &size);
    printf("后序遍历的节点打印序列 = ");
    printArray(result, size);

    /* 前序遍历 */
    preOrderStack(root, size);
    printf("迭代前序遍历的节点打印序列 = ");
    printArray(result, size);

    /* 中序遍历 */
    inOrderStack(root, size);
    printf("迭代中序遍历的节点打印序列 = ");
    printArray(result, size);

    /* 后序遍历 */
    postOrderStack(root, size);
    printf("迭代后序遍历的节点打印序列 = ");
    printArray(result, size);

    freeMemoryTree(root);
    return 0;
}
