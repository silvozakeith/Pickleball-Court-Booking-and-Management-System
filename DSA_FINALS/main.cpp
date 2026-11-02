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
