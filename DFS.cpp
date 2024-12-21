#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// C?u trúc c?a m?t nút trong cây
struct Node {
    string tenNode;           // Tên nút
    vector<Node*> children;   // Danh sách các con c?a nút
};

// C?u trúc cây
struct Tree {
    Node* root;  // G?c c?a cây
};

// Kh?i t?o cây r?ng
void treeInit(Tree& tree) {
    tree.root = NULL;
}

// Chèn m?t nút con vào cây (n?u nút cha dã t?n t?i)
void treeInsert(Tree& tree, const string& tenNode, const string& parentName) {
    Node* newNode = new Node{tenNode};

    // N?u cây r?ng, nút m?i là g?c
    if (tree.root == NULL) {
        tree.root = newNode;
        return;
    }

    // Tìm nút cha d? thêm nút con
    stack<Node*> s;
    s.push(tree.root);

    bool parentFound = false;

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        // N?u nút cha tìm th?y, thêm nút con
        if (current->tenNode == parentName) {
            current->children.push_back(newNode);
            parentFound = true;
            break;
        }

        // Ti?p t?c duy?t qua các con
        for (int i = 0; i < current->children.size(); i++) {
            s.push(current->children[i]);
        }
    }

    if (!parentFound) {
        cout << "Khong tim thay cha: " << parentName << endl;
        delete newNode;  // H?y nút con n?u không tìm th?y cha
    }
}

// Tìm ki?m nút trong cây b?ng DFS
Node* treeSearchDFS(Tree& tree, const string& tenNode) {
    if (tree.root == NULL) {
        return NULL;  // Cây r?ng
    }

    // Duy?t cây theo DFS
    stack<Node*> s;
    s.push(tree.root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        // In ra quá trình duy?t
        cout << current->tenNode << " ";

        // N?u tìm th?y nút, tr? v?
        if (current->tenNode == tenNode) {
            cout << "\nTim thay node: " << current->tenNode << endl;
            return current;
        }

        // Ti?p t?c duy?t qua các con
        for (int i = current->children.size() - 1; i >= 0; i--) {  // Duy?t t? con cu?i cùng
            s.push(current->children[i]);
        }
    }

    cout << "\nKhong tim thay node: " << tenNode << endl;
    return NULL;  // Không tìm th?y nút
}

// Duy?t cây theo DFS
void traverseDFS(Node* node) {
    if (node == NULL) {
        return;
    }

    // In ra tên nút (tham nút hi?n t?i)
    cout << node->tenNode << " ";

    // Duy?t qua các con c?a nút
    for (int i = 0; i < node->children.size(); i++) {
        traverseDFS(node->children[i]);
    }
}

// H?y cây
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

// Hàm chính
int main() {
    Tree tree;
    treeInit(tree);

    // Kh?i t?o cây v?i các nút và các con c?a nó
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

    // Duy?t cây theo DFS
    cout << "\nDuyet cay theo DFS: ";
    traverseDFS(tree.root);
    cout << endl;

    // Tìm ki?m m?t nút
    string tenNodeTim;
    cout << "Nhap ten node can tim: ";
    getline(cin, tenNodeTim);

    treeSearchDFS(tree, tenNodeTim);

    // H?y cây
    treeDestroy(tree);
    if (tree.root == NULL) {
        cout << "Cay da duoc huy." << endl;
    }

    return 0;
}


