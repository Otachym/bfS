#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// C?u tr�c c?a m?t n�t trong c�y
struct Node {
    string tenNode;           // T�n n�t
    vector<Node*> children;   // Danh s�ch c�c con c?a n�t
};

// C?u tr�c c�y
struct Tree {
    Node* root;  // G?c c?a c�y
};

// Kh?i t?o c�y r?ng
void treeInit(Tree& tree) {
    tree.root = NULL;
}

// Ch�n m?t n�t con v�o c�y (n?u n�t cha d� t?n t?i)
void treeInsert(Tree& tree, const string& tenNode, const string& parentName) {
    Node* newNode = new Node{tenNode};

    // N?u c�y r?ng, n�t m?i l� g?c
    if (tree.root == NULL) {
        tree.root = newNode;
        return;
    }

    // T�m n�t cha d? th�m n�t con
    stack<Node*> s;
    s.push(tree.root);

    bool parentFound = false;

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        // N?u n�t cha t�m th?y, th�m n�t con
        if (current->tenNode == parentName) {
            current->children.push_back(newNode);
            parentFound = true;
            break;
        }

        // Ti?p t?c duy?t qua c�c con
        for (int i = 0; i < current->children.size(); i++) {
            s.push(current->children[i]);
        }
    }

    if (!parentFound) {
        cout << "Khong tim thay cha: " << parentName << endl;
        delete newNode;  // H?y n�t con n?u kh�ng t�m th?y cha
    }
}

// T�m ki?m n�t trong c�y b?ng DFS
Node* treeSearchDFS(Tree& tree, const string& tenNode) {
    if (tree.root == NULL) {
        return NULL;  // C�y r?ng
    }

    // Duy?t c�y theo DFS
    stack<Node*> s;
    s.push(tree.root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        // In ra qu� tr�nh duy?t
        cout << current->tenNode << " ";

        // N?u t�m th?y n�t, tr? v?
        if (current->tenNode == tenNode) {
            cout << "\nTim thay node: " << current->tenNode << endl;
            return current;
        }

        // Ti?p t?c duy?t qua c�c con
        for (int i = current->children.size() - 1; i >= 0; i--) {  // Duy?t t? con cu?i c�ng
            s.push(current->children[i]);
        }
    }

    cout << "\nKhong tim thay node: " << tenNode << endl;
    return NULL;  // Kh�ng t�m th?y n�t
}

// Duy?t c�y theo DFS
void traverseDFS(Node* node) {
    if (node == NULL) {
        return;
    }

    // In ra t�n n�t (tham n�t hi?n t?i)
    cout << node->tenNode << " ";

    // Duy?t qua c�c con c?a n�t
    for (int i = 0; i < node->children.size(); i++) {
        traverseDFS(node->children[i]);
    }
}

// H?y c�y
void treeDestroy(Tree& tree) {
    if (tree.root == NULL) return;

    stack<Node*> s;
    s.push(tree.root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        for (int i = 0; i < current->children.size(); i++) {
            s.push(current->children[i]);
        }

        delete current;
    }

    tree.root = NULL;
}

// H�m ch�nh
int main() {
    Tree tree;
    treeInit(tree);

    // Kh?i t?o c�y v?i c�c n�t v� c�c con c?a n�
    int soLuongNode;
    cout << "Nhap so luong node: ";
    cin >> soLuongNode;
    cin.ignore();  

    for (int i = 0; i < soLuongNode; i++) {
        string tenNode, parentName;
        cout << "Nhap ten node thu " << (i + 1) << ": ";
        getline(cin, tenNode);

        cout << "Nhap ten cha cua node (de trong neu la goc): ";
        getline(cin, parentName);

        treeInsert(tree, tenNode, parentName);
    }

    // Duy?t c�y theo DFS
    cout << "\nDuyet cay theo DFS: ";
    traverseDFS(tree.root);
    cout << endl;

    // T�m ki?m m?t n�t
    string tenNodeTim;
    cout << "Nhap ten node can tim: ";
    getline(cin, tenNodeTim);

    treeSearchDFS(tree, tenNodeTim);

    // H?y c�y
    treeDestroy(tree);
    if (tree.root == NULL) {
        cout << "Cay da duoc huy." << endl;
    }

    return 0;
}


