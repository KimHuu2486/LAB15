#include <iostream>
using namespace std;
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};
struct Queue {
    Node* key;
    Queue* next;
};
Queue* newQueue(Node* val) {
    Queue* temp = new Queue;
    temp->key = val;
    temp->next = NULL;
    return temp;
}
void push(Queue*& q, Node* val) {
    if (!q) {
        q = newQueue(val);
    }
    else {
        push(q->next, val);
    }
}
void pop(Queue*& q) {
    Queue* temp = q;
    q = q->next;
    delete temp;
}
Node* front(Queue* q) {
    if (q) {
        return q->key;
    }
    return NULL;
}
bool isEmpty(Queue* q) {
    return q == NULL;
}
int size(Queue* q) {
    if (!q) return 0;
    return 1 + size(q->next);
}

Node* newNode(int data) {
    Node* temp = new Node;
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}
int max(int a, int b) {
    if (a >= b) return a;
    return b;
}
int getHeight(Node* root) {
    if (root) {
        return root->height;
    }
    return 0;
}
int getBalance(Node* root) {
    if (!root) {
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}
void updateHeight(Node* root) {
    if (root) {
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    }
}
Node* RotateLL(Node* root) {
    Node* left1 = root->left;
    root->left = left1->right;
    left1->right = root;
    updateHeight(root);
    updateHeight(left1);
    return left1;
}
Node* RotateRR(Node* root) {
    Node* right1 = root->right;
    root->right = right1->left;
    right1->left = root;
    updateHeight(root);
    updateHeight(right1);
    return right1;
}
Node* RotateLR(Node* root) {
    root->left = RotateRR(root->left);
    return RotateLL(root);
}
Node* RotateRL(Node* root) {
    root->right = RotateLL(root->right);
    return RotateRR(root);
}
Node* insertNode(Node* root, int data) {
    if (!root) {
        return newNode(data);
    }
    if (root->key > data) {
        root->left = insertNode(root->left, data);
    }
    else if (root->key < data) {
        root->right = insertNode(root->right, data);
    }
    else return root;
    updateHeight(root);
    int bal = getBalance(root);
    if (bal < -1) {
        if (data > root->right->key) {
            return RotateRR(root);
        }
        else return RotateRL(root);
    }
    else if (bal > 1) {
        if (data < root->left->key) {
            return RotateLL(root);
        }
        else return RotateLR(root);
    }
    return root;
}
Node* searchNode(Node* root, int data) {
    if (!root) return NULL;
    if (root->key == data) return root;
    else if (root->key > data) {
        return searchNode(root->left, data);
    }
    else return searchNode(root->right, data);
}
Node* deleteNode(Node* root, int data) {
    if (!root) return root;
    if (root->key < data) {
        root->right = deleteNode(root->right, data);
    }
    else if (root->key > data) {
        root->left = deleteNode(root->left, data);
    }
    else {
        if (!root->left || !root->right) {
            Node* temp = root;
            if (root->left) {
                root = root->left;
            }
            else root = root->right;
            delete temp;
        }
        else {
            Node* temp = root->left;
            while (temp->right) {
                temp = temp->right;
            }
            root->key = temp->key;
            root->left = deleteNode(root->left, temp->key);
        }
    }
    if (!root) return root;
    updateHeight(root);
    int bal = getBalance(root);
    if (bal < -1) {
        if (getBalance(root->right) <= 0) {
            root = RotateRR(root);
        }
        else root = RotateRL(root);
    }
    else if (bal > 1) {
        if (getBalance(root->left) >= 0) {
            root = RotateLL(root);
        }
        else root = RotateLR(root);
    }
    return root;
}
void NLR(Node* root) {
    if (root) {
        cout << root->key << " ";
        NLR(root->left);
        NLR(root->right);
    }
}
void LNR(Node* root) {
    if (root) {
        LNR(root->left);
        cout << root->key << " ";
        LNR(root->right);
    }
}
void LRN(Node* root) {
    if (root) {
        LRN(root->left);
        LRN(root->right);
        cout << root->key << " ";
    }
}
void LevelOrder(Node* root) {
    if (!root) {
        cout << "NULL" << endl;
        return;
    }
    Queue* q = NULL;
    push(q, root);
    while (!isEmpty(q)) {
        int n = size(q);
        for (int i = 1; i <= n; i++) {
            Node* cur = front(q);
            pop(q);
            if (cur) {
                cout << cur->key << " ";
                if (cur->left) {
                    push(q, cur->left);
                }
                if (cur->right) {
                    push(q, cur->right);
                }
            }
        }
    }
}
int main()
{
    Node* root = NULL;
    root = insertNode(root, 2);
    root = insertNode(root, 1);
    root = insertNode(root, 0);
    root = insertNode(root, 3);
    root = insertNode(root, 4);
    root = insertNode(root, 5);
    root = insertNode(root, 6);

    NLR(root);
    cout << endl;
    LNR(root);
    cout << endl;
    LRN(root);
    cout << endl;
    LevelOrder(root);
    cout << endl;

    Node* res = searchNode(root, 5);
    if (res) {
        cout << "FOUND!!!" << endl;
    }
    else cout << "NOT FOUND!!!" << endl;
    res = searchNode(root, 7);
    if (res) {
        cout << "FOUND!!!" << endl;
    }
    else cout << "NOT FOUND!!!" << endl;

    root = deleteNode(root, 3);
    root = deleteNode(root, 1);
    root = deleteNode(root, 0);
    LevelOrder(root);
    cout << endl;

    return 0;
}