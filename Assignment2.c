#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

struct Node* create(int arr[], int size) {
    struct Node* root = NULL;
    for (int i = 0; i < size; i++)
        root = insert(root, arr[i]);
    return root;
}

struct Node* min(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = min(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
int getHeight(struct Node* root) {
    if (root == NULL) return -1;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
void print(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found\n");
        return;
    }

    if (root->data == key) {
        printf("Level: %d, Height: %d\n", level, getHeight(root));
        return;
    }

    if (key < root->data)
        print(root->left, key, level + 1);
    else
        print(root->right, key, level + 1);
}
void allocate(struct Node* root) {
    if (root != NULL) {
        allocate(root->left);
        allocate(root->right);
        free(root);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int size = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = create(arr, size);

    printf("Height of BST: %d\n", getHeight(root));

    int deleted = 20;
    root = deleteNode(root, deleted);
    printf("Node %d deleted\n", deleted);

    printf("Height of BST after deletion: %d\n", getHeight(root));

    int nodeKey = 30;
    printf("Level and Height of Node %d:\n", nodeKey);
    print(root, nodeKey, 0);

    allocate(root);

    return 0;
}
