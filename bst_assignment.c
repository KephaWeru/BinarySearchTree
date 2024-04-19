/*
Kepha Weru      SCT221-0218/2022
Keith Kihara    SCT221-0217/2022
*/

#include <stdio.h>
#include <stdlib.h>

// Define a structure for the binary search tree node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to find the index of a value in an array
int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1; // Not found
}

// Function to construct the binary search tree from in-order and post-order traversals
TreeNode* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;

    // Create a new node with the current post-order element
    TreeNode* node = createNode(postOrder[(*postIndex)--]);

    if (inStart == inEnd)
        return node;

    // Find the index of current node in in-order traversal
    int inIndex = findIndex(inOrder, inStart, inEnd, node->data);

    // Construct right and left subtrees recursively
    node->right = bst_construct(inOrder, postOrder, inIndex + 1, inEnd, postIndex);
    node->left = bst_construct(inOrder, postOrder, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to traverse the binary search tree in breadth-first-search (DFS) order
void bfs_traverse(TreeNode* root) {
    if (root == NULL)
        return;

    // Create a queue for BFS
    TreeNode* queue[100]; // Assuming a maximum of 100 nodes
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        TreeNode* current = queue[++front];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[++rear] = current->left;

        if (current->right != NULL)
            queue[++rear] = current->right;
    }
}

int main() {
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int postIndex = 6; // Start from the last index of post-order array

    TreeNode* root = bst_construct(inOrder, postOrder, 0, 6, &postIndex);

    printf("BFS Traversal: ");
    bfs_traverse(root);
    printf("\n");

    return 0;
}
