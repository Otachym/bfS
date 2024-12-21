#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

// C?u trúc c?a m?t nút trong cây
struct Node {
    string tenNode; // Tên nút
    vector<Node*> children; // Danh sách các con c?a nút
};

// C?u trúc cây
struct Tree {
    Node* root; // G?c c?a cây
};

// Kh?i t?o cây r?ng
void treeInit(Tree& tree) {
    tree.root = NULL;
}

// Chèn m?t nút m?i vào cây (không ph?i cây nh? phân, có th? có nhi?u con)
void treeInsert(Tree& tree, const string& tenNode, const string& parentName = "") {
    Node* newNode = new Node{tenNode};

    // N?u cây r?ng, nút m?i là g?c
    if (tree.root == NULL) {
        tree.root = newNode;
        return;
    }

    // Tìm nút cha, n?u có, d? thêm nút con
    if (parentName.empty()) {
        tree.root->children.push_back(newNode); // Thêm làm con c?a g?c
        return;
    }

    // Duy?t cây d? tìm nút cha
    queue<Node*> q;
    q.push(tree.root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // N?u nút cha tìm th?y, thêm nút con
        if (current->tenNode == parentName) {
            current->children.push_back(newNode);
            return;
        }

        // Ti?p t?c duy?t qua các con
        for (int i = 0; i < current->children.size(); i++) {
            q.push(current->children[i]);
        }
    }

    // N?u không tìm th?y nút cha, không thêm du?c nút con
    cout << "Khong tim thay cha: " << parentName << endl;
}

// Tìm ki?m nút trong cây
Node* treeSearch(Tree& tree, const string& tenNode) {
    if (tree.root == NULL) {
        return NULL; // Cây r?ng
    }

    // Duy?t cây theo BFS d? tìm nút
    queue<Node*> q;
    q.push(tree.root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->tenNode == tenNode) {
            return current; // Tìm th?y nút
        }

        // Ti?p t?c duy?t qua các con
        for (int i = 0; i < current->children.size(); i++) {
            q.push(current->children[i]);
        }
    }

    return NULL; // Không tìm th?y nút
}

// Duy?t cây theo BFS
void traverseBFS(Tree& tree) {
    if (tree.root == NULL) {
        cout << "Cay rong!" << endl;
        return;
    }

    queue<Node*> q;
    q.push(tree.root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->tenNode << " ";

        // Duy?t qua các con (c?p nh?t vòng l?p)
        for (int i = 0; i < current->children.size(); i++) {
            q.push(current->children[i]);
        }
    }

    cout << endl;
}

// H?y cây
void treeDestroy(Tree& tree) {
    if (tree.root == NULL) return;

    queue<Node*> q;
    q.push(tree.root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (int i = 0; i < current->children.size(); i++) {
            q.push(current->children[i]);
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
    cin.ignore(); // B? ký t? xu?ng dòng còn l?i trong b? d?m

    for (int i = 0; i < soLuongNode; i++) {
        string tenNode, parentName;
        cout << "Nhap ten node thu " << (i + 1) << ": ";
        getline(cin, tenNode);

        cout << "Nhap ten cha (de trong neu la goc): ";
        getline(cin, parentName);

        treeInsert(tree, tenNode, parentName);
    }

    // Duy?t cây theo BFS
    cout << "\nDuyet cay theo BFS: ";
    traverseBFS(tree);

    // Tìm ki?m m?t nút
    string tenNodeTim;
    cout << "Nhap ten node can tim: ";
    getline(cin, tenNodeTim);

    Node* result = treeSearch(tree, tenNodeTim);
    if (result != NULL) {
        cout << "Tim thay node: " << result->tenNode << endl;
    } else {
        cout << "Khong tim thay node: " << tenNodeTim << endl;
    }

    // H?y cây
    treeDestroy(tree);
    if (tree.root == NULL) {
        cout << "Cay da duoc huy." << endl;
    }

    return 0;
}


