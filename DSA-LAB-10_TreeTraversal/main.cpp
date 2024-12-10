#include <iostream>
#include<string>
#include <queue>
#include <limits>
using namespace std;

typedef int ElementType;

// Node structure
struct node {
    ElementType data;
    node* left;
    node* right;

    node(ElementType value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    node* root;

public:
    BinaryTree() {
        root = nullptr;
    }

    // Binary tree methods
    void Insert(ElementType info); // Insert root node
    void AddLeft(node* parent, ElementType value); // Add left child
    void AddRight(node* parent, ElementType value); // Add right child
    void InsertNode(ElementType value); // Insert node in level order
    bool IsEmpty() const;
    bool IsLeaf(node* current) const;
    node* LeftChild() const;
    node* RightChild() const;
    ElementType Data() const;
    void DisplayRoot() const;
    node* GetRoot() const { return root; }
    node* FindNode(node* current, ElementType value) const;
    node* FindSiblings(node* current, ElementType value) const;
    void PreOrderTraversal(node* root) const;
    void InOrderTraversal(node* root) const;
    void PostOrderTraversal(node* root) const;
};

// Menu display
void DisplayMenu() {
    cout << "-----------------------------------\n";
    cout << "------- ADT of Binary Trees -------\n";
    cout << "1. Insert root node\n";
    cout << "2. Insert a node\n";
    cout << "3. Display left child of root\n";
    cout << "4. Display right child of root\n";
    cout << "5. Check if a node is a leaf node\n";
    cout << "6. Display root of the tree\n";
    cout << "7. Find sibling of a node\n";
    cout << "8. Pre-order traversal\n";
    cout << "9. In-order traversal\n";
    cout << "10.Post-order traversal\n";
    cout << "11. Exit\n";
    cout << "-----------------------------------\n";
}

// Insert root node
void BinaryTree::Insert(ElementType info) {
    if (IsEmpty()) {
        root = new node(info);
    }
    else {
        cout << "Root already exists. Cannot insert another root.\n";
    }
}

// Insert node in level-order
void BinaryTree::InsertNode(ElementType value) {
    node* newNode = new node(value);
    if (IsEmpty()) {
        root = newNode;
        cout << "Inserted as root node: " << value << "\n";
        return;
    }

    queue<node*> q;
    q.push(root);

    while (!q.empty()) {
        node* current = q.front();
        q.pop();

        if (current->left == nullptr) {
            current->left = newNode;
            cout << "Inserted " << value << " as the left child of " << current->data << "\n";
            return;
        }
        else {
            q.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = newNode;
            cout << "Inserted " << value << " as the right child of " << current->data << "\n";
            return;
        }
        else {
            q.push(current->right);
        }
    }
}

// Add left child
void BinaryTree::AddLeft(node* parent, ElementType value) {
    if (!parent) {
        cout << "Parent node is null. Cannot add left child.\n";
        return;
    }
    if (!parent->left) {
        parent->left = new node(value);
        cout << "Left child added with value: " << value << "\n";
    }
    else {
        cout << "Left child already exists.\n";
    }
}

// Add right child
void BinaryTree::AddRight(node* parent, ElementType value) {
    if (!parent) {
        cout << "Parent node is null. Cannot add right child.\n";
        return;
    }
    if (!parent->right) {
        parent->right = new node(value);
        cout << "Right child added with value: " << value << "\n";
    }
    else {
        cout << "Right child already exists.\n";
    }
}

// Check if the tree is empty
bool BinaryTree::IsEmpty() const {
    return root == nullptr;
}

// Check if a node is a leaf
bool BinaryTree::IsLeaf(node* current) const {
    return current && !current->left && !current->right;
}

// Get left child of root
node* BinaryTree::LeftChild() const {
    return root ? root->left : nullptr;
}

// Get right child of root
node* BinaryTree::RightChild() const {
    return root ? root->right : nullptr;
}

// Get data from root
ElementType BinaryTree::Data() const {
    if (IsEmpty()) {
        throw runtime_error("Tree is empty!");
    }
    return root->data;
}

// Display root node
void BinaryTree::DisplayRoot() const {
    if (IsEmpty()) {
        cout << "The tree is empty.\n";
    }
    else {
        cout << "Root node data: " << root->data << "\n";
    }
}

// Find a node by value
node* BinaryTree::FindNode(node* current, ElementType value) const {
    if (!current) return nullptr;
    if (current->data == value) return current;

    node* found = FindNode(current->left, value);
    return found ? found : FindNode(current->right, value);
}

// Find sibling
node* BinaryTree::FindSiblings(node* current, ElementType value) const {
    if (!current || !current->left || !current->right) return nullptr;

    if (current->left->data == value) return current->right;
    if (current->right->data == value) return current->left;

    node* sibling = FindSiblings(current->left, value);
    return sibling ? sibling : FindSiblings(current->right, value);
}

// Pre-order traversal
void BinaryTree::PreOrderTraversal(node* root) const {
    if (!root) return;
    cout << root->data << " ";
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

// In-order traversal
void BinaryTree::InOrderTraversal(node* root) const {
    if (!root) return;
    InOrderTraversal(root->left);
    cout << root->data << " ";
    InOrderTraversal(root->right);
}

// Post-order traversal
void BinaryTree::PostOrderTraversal(node* root) const {
    if (!root) return;
    PostOrderTraversal(root->left);
    PostOrderTraversal(root->right);
    cout << root->data << " ";
}

// Main
int main() {
    BinaryTree tree;
    string choice;
    ElementType value;

    while (true) {
        DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1") {
            cout << "Enter value for root node: ";
            while (!(cin >> value)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            tree.Insert(value);
        }
        else if (choice == "2") {
            cout << "Enter value to insert: ";
            while (!(cin >> value)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            tree.InsertNode(value);
        }
        else if (choice == "3") {
            node* left = tree.LeftChild();
            cout << (left ? "Left child: " + to_string(left->data) : "No left child.") << "\n";
        }
        else if (choice == "4") {
            node* right = tree.RightChild();
            cout << (right ? "Right child: " + to_string(right->data) : "No right child.") << "\n";
        }
        else if (choice == "5") {
            cout << "Enter node value to check if it's a leaf: ";
            while (!(cin >> value)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            node* target = tree.FindNode(tree.GetRoot(), value);
            cout << (tree.IsLeaf(target) ? "Node is a leaf." : "Node is not a leaf or doesn't exist.") << "\n";
        }
        else if (choice == "6") {
            tree.DisplayRoot();
        }
        else if (choice == "7") {
            cout << "Enter node value to find sibling: ";
            while (!(cin >> value)) {
                cout << "Invalid input. Please enter an integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            node* sibling = tree.FindSiblings(tree.GetRoot(), value);
            cout << (sibling ? "Sibling: " + to_string(sibling->data) : "No sibling.") << "\n";
        }
        else if (choice == "8") {
            cout << "Pre-order: ";
            tree.PreOrderTraversal(tree.GetRoot());
            cout << "\n";
        }
        else if (choice == "9") {
            cout << "In-order: ";
            tree.InOrderTraversal(tree.GetRoot());
            cout << "\n";
        }
        else if (choice == "10") {
            cout << "Post-order: ";
            tree.PostOrderTraversal(tree.GetRoot());
            cout << "\n";
        }
        else if (choice == "11") {
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
