#include <iostream>
#include <string>
using namespace std;

// Pickle ball court booking system

//Module 2: Sturcts and Data types
struct Booking {
    int courtNo;
    int startHour;
    int startMin;
    bool isStartAM;
    int endHour;
    int endMin;
    bool isEndAM;
    string playerName;
    string contact;
    float fee;
};

// Modulke 9: Binary search tree
struct Node {
    Booking data;
    Node* left;
    Node* right;
    Node(Booking booking) : data(booking), left(nullptr), right(nullptr) {}
};
Node* root = nullptr;

// Module 4: Stack and Undo functions
struct StackNode {
    Booking data;
    StackNode* next;
};
StackNode* top = nullptr;
void pushToStack(Booking b) {
    StackNode* newNode = new StackNode{b, top};
    top = newNode;
}

bool popFromStack(Booking &out) {
    if (!top) return false;
    StackNode* temp = top;
    out = temp->data;
    top = top->next;
    delete temp;
    return true;
}
// Module 9: BST Functions
Node* insertBST(Node* node, Booking b) {
    if (!node) return new Node(b);
    if (getKey(b) < getKey(node->data))
        node->left = insertBST(node->left, b);
    else
        node->right = insertBST(node->right, b);
    return node;
}

// Module 6: Searching
bool searchBST(Node* node, int court, int hour, int min, bool isAM, Booking &result) {
    if (!node) return false;
    int targetTime = to24Hour(hour, isAM) * 100 + min;
    int targetKey = court * 10000 + targetTime;
    int currKey = getKey(node->data);
    
    if (targetKey == currKey) {
        result = node->data;
        return true;
    }
    if (targetKey < currKey)
        return searchBST(node->left, court, hour, min, isAM, result);
    else
        return searchBST(node->right, court, hour, min, isAM, result);
}









// main
void menu () {
    int
