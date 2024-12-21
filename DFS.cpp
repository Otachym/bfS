#include <iostream>
#include <string>
#include <vector>
#include <stack>

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

void treeInsert(Tree& tree, const string& tenNode, const string& parentName) {
    Node* newNode = new Node{tenNode};

    if (tree.root == NULL) {
        tree.root = newNode;
        return;
    }

    stack<Node*> s;
    s.push(tree.root);

    bool parentFound = false;

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();

        if (current->tenNode == parentName) {
            current->children.push_back(newNode);
            parentFound = true;
            break;
        }

        for (int i = 0; i < current->children.size(); i++) {
            s.push(current->children[i]);
        }
    }

    if (!parentFound) {
        cout << "Khong tim thay cha: " << parentName << endl;
        delete newNode;
    }
}

void traverseDFS(Node* node) {
    if (node == NULL) {
        return;
    }

    cout << node->tenNode << " ";

    for (int i = 0; i < node->children.size(); i++) {
        traverseDFS(node->children[i]);
    }
}

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

        cout << "Nhap ten cha cua node (de trong neu la goc): ";
        getline(cin, parentName);

        treeInsert(tree, tenNode, parentName);
    }

    cout << "\nDuyet cay theo DFS: ";
    traverseDFS(tree.root);
    cout << endl;

    treeDestroy(tree);


    return 0;
}
