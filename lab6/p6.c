// Binary Search Tree ADT using linked list
#include <stdio.h>
#include <stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
    int value;
    Tree left;
    Tree right;
};

/*  
    insert a new node with the key value into the tree.
    If the key already exists in the tree, print an error message.
*/
Tree insertNode(Tree root, int key) {
    if(root == NULL) {
        root = malloc(sizeof(struct BinarySearchTree));
        root->value = key;
        root->right = NULL;
        root->left = NULL;
        printf("Insert %d\n", key);
    } else if(key > root->value) {
        root->right = insertNode(root->right, key);
    } else if(key < root->value) {
        root->left = insertNode(root->left, key);
    } else if(key == root->value) {
        perror("Insertion Error: ");
        printf("There is already %d in the tree\n", key);
    }
    return root;
}
/*
    Get max value in subtree of a node, return the max value node
    (used to reform tree in deleteNode)
*/
Tree getMaxValueInTree(Tree root) {
    if(root == NULL) {
        return NULL;
    } else {
        while(root->right != NULL) {
            root = root->right;
        }
        return root;
    }
}

/*
    delete a node with the given key value from the tree.
    Reform tree using left subtree, If the key does not eixt in the tree,
    print an error message.
*/
Tree deleteNode(Tree root, int key) {
    Tree TmpNode;
    if(root == NULL) {
        perror("Deletion Error: ");
        printf("%d is not in the tree.\n", key);
    } else if(key < root->value) {
        root->left = deleteNode(root->left, key);
    } else if(key > root->value) {
        root->right = deleteNode(root->right, key);
    } else if(root->left && root->right) {
        TmpNode = getMaxValueInTree(root->left);
        printf("Delete %d\n", root->value);
        root->value = TmpNode->value;
        root->left = deleteNode(root->left, root->value);
    } else {
        TmpNode = root;
        if(root->left == NULL) {
            root = root->left;
        } else if(root->right == NULL) {
            root = root->left;
        }
        free(TmpNode);
    }
    return root;
}

/*
    Find the key in the binary search tree. Print "[key] is in the tree" 
    if the key exist. Otherwise, print "[key] is not in the tree."
*/
void findNode(Tree root, int key) {
    if(root == NULL) {
        printf("%d is not in the tree.\n", key);
    } else if(key < root->value) {
        findNode(root->left, key);
    } else if(key > root->value) {
        findNode(root->right, key);
    } else if(key == root->value) {
        printf("%d is in the tree.\n", root->value);
    }
}

void printPreorder(Tree root) {
    if(root == NULL) {
        return;
    }
    printf("%d ", root->value);
    printPreorder(root->left);
    printPreorder(root->right);

}
void printInorder(Tree root) {
    if(root == NULL) {
        return;
    }
    printInorder(root->left);
    printf("%d ", root->value);
    printInorder(root->right);
}
void printPostorder(Tree root) {
    if(root == NULL) {
        return;
    }
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d ", root->value);
}



int main(int argc, char* argv[]) {
    FILE *fi = fopen(argv[1], "r");
    char cmd;
    int key;

    Tree root = NULL;
    while(!feof(fi)) {
        fscanf(fi, "%c", &cmd);
        switch(cmd) {
            case 'i':
                fscanf(fi, "%d", &key);
                root = insertNode(root, key);
                break;
            case 'd':
                fscanf(fi, "%d", &key);
                root = deleteNode(root, key);
                break;
            case 'p':
                fscanf(fi, "%c", &cmd);
                if(cmd == 'i') {
                    printInorder(root);
                } else if(cmd == 'r') {
                    printPreorder(root);
                } else if(cmd == 'o') {
                    printPostorder(root);
                }
                printf("\n");
                break;
            case 'f':
                fscanf(fi, "%d", &key);
                findNode(root, key);
                break;
            default:
                break;
        }
    }
}
