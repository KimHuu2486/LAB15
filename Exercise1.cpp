#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
    int height;

    Node(int v): val(v), left(nullptr), right(nullptr), height(1){}
};
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
        return new Node(data);
    }
    if (root->val > data) {
        root->left = insertNode(root->left, data);
    }
    else if (root->val < data) {
        root->right = insertNode(root->right, data);
    }
    else return root;
    updateHeight(root);
    int bal = getBalance(root);
    if (bal < -1) {
        if (data > root->right->val) {
            return RotateRR(root);
        }
        else return RotateRL(root);
    }
    else if (bal > 1) {
        if (data < root->left->val) {
            return RotateLL(root);
        }
        else return RotateLR(root);
    }
    return root;
}
bool findPath(Node* root, int val, vector<int>& path) {
    if (!root) return false;
    path.push_back(root->val);
    if (root->val > val) {
        return findPath(root->left, val, path);
    }
    else if (root->val < val) {
        return findPath(root->right, val, path);
    }
    else return true;
}
int findLCA(Node* root, int p, int q) {
    vector<int>pathP, pathQ;
    if (!findPath(root, p, pathP)) return 0;
    if (!findPath(root, q, pathQ)) return 0;

    int idx = 0;
    while (pathP[idx] == pathQ[idx]) {
        idx++;
    }
    return pathP[idx-1];
}
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int main()
{
    int n;
    cin >> n;
    vector<int>values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    int p, q;
    cin >> p >> q;
    Node* root = nullptr;
    for (int val : values) {
        root = insertNode(root, val);
    }
    
    int lca = findLCA(root, p, q);
    cout << lca << endl;

    deleteTree(root);
    return 0;
}
