#include <iostream>
#include <string>
using namespace std;


//Module 2
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

//Module 5
struct QueueNode {
    string name;
    string contact;
    QueueNode* next;
};
QueueNode* qFront = nullptr;
QueueNode* qRear = nullptr;


void enqueueWaitlist(string n, string c) {
    QueueNode* newNode = new QueueNode{n, c, nullptr};
    if (!qRear) {
        qFront = qRear = newNode;
        return;
    }
    qRear->next = newNode;
    qRear = newNode;
}


bool dequeueWaitlist(string &outName, string &outContact) {
    if (!qFront) return false;
    QueueNode* temp = qFront;
    outName = temp->name;
    outContact = temp->contact;
    qFront = qFront->next;
    if (!qFront) qRear = nullptr;
    delete temp;
    return true;
}


// ========== HELPER FUNCTIONS ==========
int to24Hour(int h, bool isAM) {
    if (isAM) {
        if (h == 12) return 0;
        return h;
    } else {
        if (h == 12) return 12;
        return h + 12;
    }
}


int getKey(Booking b) {
    int startTotal = to24Hour(b.startHour, b.isStartAM) * 100 + b.startMin;
    return b.courtNo * 10000 + startTotal;
}


//Module 9
struct Node {
    Booking data;
    Node* left;
    Node* right;
    Node(Booking b) : data(b), left(nullptr), right(nullptr) {}
};
Node* root = nullptr;

//Module 4
struct StackNode {
    Booking data;
    StackNode* next;
};
StackNode* stackTop = nullptr;

void pushToStack(Booking b) {
    StackNode* newNode = new StackNode{b, stackTop};
    stackTop = newNode;
}

bool popFromStack(Booking &out) {
    if (!stackTop) return false;
    StackNode* temp = stackTop;
    out = temp->data;
    stackTop = stackTop->next;
    delete temp;
    return true;
}

//Module 5
struct QueueNode {
    string name;
    string contact;
    QueueNode* next;
};
QueueNode* qFront = nullptr;
QueueNode* qRear = nullptr;

void enqueueWaitlist(string n, string c) {
    QueueNode* newNode = new QueueNode{n, c, nullptr};
    if (!qRear) {
        qFront = qRear = newNode;
        return;
    }
    qRear->next = newNode;
    qRear = newNode;
}

bool dequeueWaitlist(string &outName, string &outContact) {
    if (!qFront) return false;
    QueueNode* temp = qFront;
    outName = temp->name;
    outContact = temp->contact;
    qFront = qFront->next;
    if (!qFront) qRear = nullptr;
    delete temp;
    return true;
}

//helper function
int to24Hour(int h, bool isAM) {
    if (isAM) {
        if (h == 12) return 0;
        return h;
    } else {
        if (h == 12) return 12;
        return h + 12;
    }
}

int getKey(Booking b) {
    int startTotal = to24Hour(b.startHour, b.isStartAM) * 100 + b.startMin;
    return b.courtNo * 10000 + startTotal;
}

//Module 9
Node* insertBST(Node* node, Booking b) {
    if (!node) return new Node(b);
    if (getKey(b) < getKey(node->data))
        node->left = insertBST(node->left, b);
    else
        node->right = insertBST(node->right, b);
    return node;
}

//Module 6
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

//Module 7 and 8
string formatTime(int h, int m, bool isAM) {
    string period = isAM ? "AM" : "PM";
    string minStr = (m < 10) ? "0" + to_string(m) : to_string(m);
    return to_string(h) + ":" + minStr + " " + period;
}

void displaySorted(Node* node) {
    if (!node) return;
    displaySorted(node->left);
    cout << "Court " << node->data.courtNo 
         << " | " << formatTime(node->data.startHour, node->data.startMin, node->data.isStartAM)
         << " to " << formatTime(node->data.endHour, node->data.endMin, node->data.isEndAM)
         << " | " << node->data.playerName 
         << " | Fee: P" << node->data.fee << "\n";
    displaySorted(node->right);
}

//main
void menu() {
    int choice;
    do {
        cout << "\n===== PICKLEBALL COURT BOOKING SYSTEM =====\n";
        cout << "[1] Book Court\n";
        cout << "[2] View Schedule\n";
        cout << "[3] Process Waitlist\n";
        cout << "[4] Search Booking\n";
        cout << "[5] Undo Last Booking\n";
        cout << "[0] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Booking b;
            cout << "\n--- New Booking ---\n";
            cout << "Enter Court Number (1-4): ";
            cin >> b.courtNo;
            
            if (b.courtNo < 1 || b.courtNo > 4) {
                cout << "Error: Only Court 1 to Court 4 are available\n";
                continue;
            }
            
            cout << "Enter Start Hour (1-12): ";
            cin >> b.startHour;
            cout << "Enter Start Minute (00-59): ";
            cin >> b.startMin;
            char startPeriod;
            cout << "AM or PM? Enter A for AM, P for PM: ";
            cin >> startPeriod;
            b.isStartAM = (startPeriod == 'A' || startPeriod == 'a');
            
            cout << "Enter End Hour (1-12): ";
            cin >> b.endHour;
            cout << "Enter End Minute (00-59): ";
            cin >> b.endMin;
            char endPeriod;
            cout << "AM or PM? Enter A for AM, P for PM: ";
            cin >> endPeriod;
            b.isEndAM = (endPeriod == 'A' || endPeriod == 'a');
            
            int startTotal = to24Hour(b.startHour, b.isStartAM) * 100 + b.startMin;
            if (startTotal < 800 || startTotal > 2000) {
                cout << "Error: Operating hours are 8:00 AM to 8:00 PM only\n";
                continue;
            }
            
            cin.ignore();
            cout << "Enter Player Name: ";
            getline(cin, b.playerName);
            cout << "Enter Contact Information: ";
            getline(cin, b.contact);
            cout << "Enter Fee Amount: ";
            cin >> b.fee;

            Booking check;
            if (searchBST(root, b.courtNo, b.startHour, b.startMin, b.isStartAM, check)) {
                cout << "\nThis time slot is already booked. Player added to waitlist.\n";
                enqueueWaitlist(b.playerName, b.contact);
            } else {
                root = insertBST(root, b);
                pushToStack(b);
                cout << "\nBooking Confirmed.\n";
                cout << "Court " << b.courtNo << " reserved for " << b.playerName << "\n";
            }
        }
        else if (choice == 2) {
            cout << "\n===== Daily Schedule (Sorted by Time) =====\n";
            displaySorted(root);
        }
        else if (choice == 3) {
            string name, contact;
            if (dequeueWaitlist(name, contact))
                cout << "\nNext player on waitlist: " << name << " - " << contact << "\n";
            else
                cout << "\nWaitlist is empty\n";
        }
        else if (choice == 4) {
            int court, hour, minute;
            bool isAM;
            Booking result;
            char period;
            
            cout << "\n--- Search Booking ---\n";
            cout << "Enter Court Number (1-4): ";
            cin >> court;
            cout << "Enter Start Hour (1-12): ";
            cin >> hour;
            cout << "Enter Start Minute (00-59): ";
            cin >> minute;
            cout << "AM or PM? Enter A for AM, P for PM: ";
            cin >> period;
            isAM = (period == 'A' || period == 'a');
            
            if (searchBST(root, court, hour, minute, isAM, result))
                cout << "\nBooking Found: " << result.playerName 
                     << " | " << formatTime(result.startHour, result.startMin, result.isStartAM) << "\n";
            else
                cout << "\nNo booking found for the selected time slot\n";
        }
        else if (choice == 5) {
            Booking undone;
            if (popFromStack(undone))
                cout << "\nUndo Complete. Booking removed for " << undone.playerName << "\n";
            else
                cout << "\nNo previous booking to undo\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}
