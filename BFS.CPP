#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    string tenNode;
    vector<Node*> children;
};

struct Tree {
    Node* root;
};

void treeInit(Tree& tree) {
    tree.root = NULL;
}

void treeInsert(Tree& tree, const string& tenNode, const string& parentName = "") {
    Node* newNode = new Node{tenNode};

    if (tree.root == NULL) {
        tree.root = newNode;
        return;
    }

    if (parentName.empty()) {
        tree.root->children.push_back(newNode);
        return;
    }

    queue<Node*> q;
    q.push(tree.root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->tenNode == parentName) {
            current->children.push_back(newNode);
            return;
        }

        for (int i = 0; i < current->children.size(); i++) {
            q.push(current->children[i]);
        }
    }

    cout << "Khong tim thay cha: " << parentName << endl;
}

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

        for (int i = 0; i < current->children.size(); i++) {
            q.push(current->children[i]);
        }
    }

    cout << endl;
}

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

int main() {
    Tree tree;
    treeInit(tree);

    int soLuongNode;
    cout << "Nhap so luong node: ";
    cin >> soLuongNode;
    cin.ignore();

    for (int i = 0; i < soLuongNode; i++) {
        string tenNode, parentName;
        cout << "Nhap ten node thu " << (i + 1) << ": ";
        getline(cin, tenNode);

        cout << "Nhap ten cha (de trong neu la goc): ";
        getline(cin, parentName);

        treeInsert(tree, tenNode, parentName);
    }

    cout << "\nDuyet cay theo BFS: ";
    traverseBFS(tree);

    treeDestroy(tree);
    return 0;
}
