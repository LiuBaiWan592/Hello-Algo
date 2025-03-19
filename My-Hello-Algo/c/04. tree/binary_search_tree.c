/**
 * @FileName    :binary_search_tree.c
 * @Date        :2024-09-04 10:35:47
 * @Author      :LiuBaiWan (https://github.com/LiuBaiWan592)
 * @Version     :V1.0.0
 * @Brief       :二叉搜索树（binary search tree）
 * @Description :1. 对于根节点，左子树中所有节点的值 < 根节点的值 < 右子树中所有节点的值。
 *               2. 任意节点的左、右子树也是二叉搜索树，即同样满足条件 1. 。
 *
 *               二叉搜索树的中序遍历序列是升序的
 */

#include "../utils/common.h"

/* 二叉搜索树结构体 */
typedef struct
{
    TreeNode *root;
} BinarySearchTree;

/* 构造函数 */
BinarySearchTree *newBinarySearchTree() {
    // 初始化空树
    BinarySearchTree *bst = malloc(sizeof(BinarySearchTree));
    bst->root = NULL;
    return bst;
}

/* 析构函数 */
void delBinarySearchTree(BinarySearchTree *bst) {
    free(bst->root);
    free(bst);
}

/* 获取二叉树根节点 */
TreeNode *getRoot(BinarySearchTree *bst) {
    return bst->root;
}

/* 查找节点 */
TreeNode *search(BinarySearchTree *bst, int num) {
    TreeNode *cur = bst->root;
    // 循环查找，越过叶节点后跳出
    while (cur != NULL) {
        if (cur->val < num) {
            // 目标节点在 cur 的右子树中
            cur = cur->right;
        } else if (cur->val > num) {
            // 目标节点在 cur 的左子树中
            cur = cur->left;
        } else {
            // 找到目标节点，跳出循环
            break;
        }
    }
    // 返回目标节点，若没有找到目标节点，返回空
    return cur;
}

/* 插入节点 */
void insert(BinarySearchTree *bst, int num) {
    // 若树为空，则初始化二叉搜索树根节点
    if (bst->root == NULL) {
        bst->root = newTreeNode(num);
        return;
    }

    TreeNode *cur = bst->root;
    TreeNode *pre = NULL;
    // 循环查找，越过叶节点后跳出
    while (cur != NULL) {
        // 找到重复节点，直接返回
        if (cur->val == num) {
            return;
        }
        pre = cur;
        if (cur->val > num) {
            // 插入位置在 cur 的左子树中
            cur = cur->left;
        } else {
            // 插入位置在 cur 的右子树中
            cur = cur->right;
        }
    }

    // 找到相应的叶子节点后，插入节点为叶子节点的子节点
    TreeNode *node = newTreeNode(num);
    if (pre->val < num) {
        pre->right = node;
    } else {
        pre->left = node;
    }
}

/* 删除节点 */
void removeItem(BinarySearchTree *bst, int num) {
    // 若树为空，直接提前返回
    if (bst->root == NULL) {
        return;
    }

    TreeNode *cur = bst->root;
    TreeNode *pre = NULL;
    // 循环查找，越过叶节点后跳出
    while (cur != NULL) {
        // 找到重复节点，直接返回
        if (cur->val == num) {
            break;
        }
        pre = cur;
        if (cur->val > num) {
            // 插入位置在 cur 的左子树中
            cur = cur->left;
        } else {
            // 插入位置在 cur 的右子树中
            cur = cur->right;
        }
    }

    // 若无待删除节点，则直接返回
    if (cur == NULL) {
        return;
    }
    // 判断待删除节点是否存在子节点
    if (cur->left == NULL || cur->right == NULL) {
        // 当子节点数量 = 0 或 1 时， child = nullptr 或 该非空子节点
        TreeNode *child = cur->left == NULL ? cur->right : cur->left;
        // 删除节点 cur
        if (pre->left == cur) {
            // 当要删除的节点时左节点时，更新父节点的左节点为child
            pre->left = child;
        } else {
            // 否则更新有节点
            pre->right = child;
        }
        // 释放要删除节点内存
        free(cur);
    } else {
        // 当要删除节点的度为2时，子节点数量等于 2。我们无法直接删除它，而需要使用一个节点替换该节点。
        // 由于要保持二叉搜索树“左子树 < 根节点 < 右子树”的性质，因此这个节点可以是右子树的最小节点或左子树的最大节点。
        // 我们选择右子树的最小节点（中序遍历的下一个节点）
        // 获取中序遍历中 cur 的下一个节点，为其右子树的最左节点
        TreeNode *next = cur->right;
        while (next->left != NULL) {
            next = next->left;
        }
        int nextVal = next->val;
        // 递归删除节点 next
        removeItem(bst, nextVal);
        // 覆盖要删除的节点的值
        cur->val = nextVal;
    }
}

/* Driver Code */
int main() {
    /* 初始化二叉搜索树 */
    int nums[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    BinarySearchTree *bst = newBinarySearchTree();
    for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
        insert(bst, nums[i]);
    }
    printf("初始化的二叉树为\n");
    printTree(getRoot(bst));

    /* 查找节点 */
    TreeNode *node = search(bst, 7);
    printf("查找到的节点对象的节点值 = %d\n", node->val);

    /* 插入节点 */
    insert(bst, 16);
    printf("插入节点 16 后，二叉树为\n");
    printTree(getRoot(bst));

    /* 删除节点 */
    removeItem(bst, 1);
    printf("删除节点 1 后，二叉树为\n");
    printTree(getRoot(bst));
    removeItem(bst, 2);
    printf("删除节点 2 后，二叉树为\n");
    printTree(getRoot(bst));
    removeItem(bst, 4);
    printf("删除节点 4 后，二叉树为\n");
    printTree(getRoot(bst));

    // 释放内存
    delBinarySearchTree(bst);
    return 0;
}
