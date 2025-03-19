/**
 * @FileName    :binary_tree.c
 * @Date        :2024-09-01 11:03:27
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :二叉树基本操作
 * @Description :二叉树节点结构体、初始化二叉树、插入与删除节点
 */

#include "../utils/common.h"

// /* 二叉树节点结构体 */
// typedef struct TreeNode
// {
//     int val;                // 节点值
//     int height;             // 节点高度
//     struct TreeNode *left;  // 左子节点指针
//     struct TreeNode *right; // 右子节点指针
// } TreeNode;

// /* 构造函数 */
// TreeNode *newTreeNode(int val)
// {
//     TreeNode *node = malloc(sizeof(TreeNode));
//     node->val = val;
//     node->height = 0;
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

int main() {
    /* 初始化二叉树 */
    // 初始化节点
    TreeNode *n1 = newTreeNode(1);
    TreeNode *n2 = newTreeNode(2);
    TreeNode *n3 = newTreeNode(3);
    TreeNode *n4 = newTreeNode(4);
    TreeNode *n5 = newTreeNode(5);
    // 构建节点之间的引用（指针）
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    printf("初始化二叉树\n");
    printTree(n1);

    /* 插入与删除节点 */
    TreeNode *P = newTreeNode(0);
    // 在 n1 -> n2 中间插入节点 P
    P->left = n1->left;
    n1->left = P;
    printf("\n插入节点 P 后\n");
    printTree(n1);

    // 删除节点 P
    n1->left = P->left;
    free(P);
    printf("\n删除节点 P 后\n");
    printTree(n1);

    freeMemoryTree(n1);
    return 0;
}