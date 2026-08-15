#include <iostream>
#include <string>

using namespace std;

const int MAX = 100;

// == DATA STRUCTURE FOR BOOK ==

struct Book {
    int bookID;
    string title;
    string author;
};

Book inputBook() {
    Book b;
    cout << "  Enter Book ID: ";
    cin >> b.bookID;
    cin.ignore();
    cout << "  Enter Title: ";
    getline(cin, b.title);
    cout << "  Enter Author: ";
    getline(cin, b.author);
    return b;
}

//  PRINT FUNCTION

void printBook(Book b) {
    cout << "[ID: " << b.bookID << 
    "] Book Title: " <<b.title << 
    " | Author: " << b.author << "\n";
}


// 1. SORTED ARRAY

Book arrData[MAX];
int arrCount = 0;

void insertArray() {
    if (arrCount >= MAX) {
        cout << "Array is full!\n";
        return;
    }
    Book b = inputBook();
    int i = arrCount - 1;
    while (i >= 0 && arrData[i].bookID > b.bookID) {
        arrData[i + 1] = arrData[i];
        i--;
    }
    arrData[i + 1] = b;
    arrCount++;
    cout << "Book inserted into sorted array.\n";
}

void deleteArray() {
    if (arrCount == 0) {
        cout << "Array is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;
    int pos = -1;
    for (int i = 0; i < arrCount; i++) {
        if (arrData[i].bookID == id) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        cout << "Book ID not found.\n";
        return;
    }
    for (int i = pos; i < arrCount - 1; i++) {
        arrData[i] = arrData[i + 1];
    }
    arrCount--;
    cout << "Book deleted from array.\n";
}

void searchArray() {
    if (arrCount == 0) {
        cout << "Array is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    int lo = 0, hi = arrCount - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (arrData[mid].bookID == id) {
            cout << "Found at index " << mid << ":\n";
            printBook(arrData[mid]);
            return;
        } else if (arrData[mid].bookID < id) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << "Book ID not found.\n";
}

void displayArray() {
    if (arrCount == 0) {
        cout << "Array is empty!\n";
        return;
    }
    cout << "-- Sorted Array of Books --\n";
    for (int i = 0; i < arrCount; i++) {
        printBook(arrData[i]);
    }
}

// 2. SORTED LINKED LIST

struct ListNode {
    Book data;
    ListNode *next;
};
ListNode *listHead = nullptr;

void insertList() {
    Book b = inputBook();
    ListNode *node = new ListNode{b, nullptr};
    if (!listHead || listHead->data.bookID >= b.bookID) {
        node->next = listHead;
        listHead = node;
        cout << "Book inserted into linked list.\n";
        return;
    }
    ListNode *cur = listHead;
    while (cur->next && cur->next->data.bookID < b.bookID) {
        cur = cur->next;
    }
    node->next = cur->next;
    cur->next = node;
    cout << "Book inserted into linked list.\n";
}

void deleteList() {
    if (!listHead) {
        cout << "Linked list is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;
    if (listHead->data.bookID == id) {
        ListNode *tmp = listHead;
        listHead = listHead->next;
        delete tmp;
        cout << "Book deleted from linked list.\n";
        return;
    }
    ListNode *cur = listHead;
    while (cur->next && cur->next->data.bookID != id) {
        cur = cur->next;
    }
    if (!cur->next) {
        cout << "Book ID not found.\n";
        return;
    }
    ListNode *tmp = cur->next;
    cur->next = tmp->next;
    delete tmp;
    cout << "Book deleted from linked list.\n";
}

void searchList() {
    if (!listHead) {
        cout << "Linked list is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    ListNode *cur = listHead;
    while (cur) {
        if (cur->data.bookID == id) {
            cout << "Book found:\n";
            printBook(cur->data);
            return;
        }
        cur = cur->next;
    }
    cout << "Book ID not found.\n";
}

void displayList() {
    if (!listHead) {
        cout << "Linked list is empty!\n";
        return;
    }
    cout << "-- Linked List of Books --\n";
    ListNode *cur = listHead;
    while (cur) {
        printBook(cur->data);
        cur = cur->next;
    }
}

// ============== 3. STACK =================
struct StackNode {
    Book data;
    StackNode *next;
};
StackNode *stackTop = nullptr;

void pushStack() {
    Book b = inputBook();
    StackNode *node = new StackNode{b, stackTop};
    stackTop = node;
    cout << "Book pushed onto stack.\n";
}

void popStack() {
    if (!stackTop) {
        cout << "Stack is empty!\n";
        return;
    }
    StackNode *tmp = stackTop;
    cout << "Popped book:\n";
    printBook(tmp->data);
    stackTop = stackTop->next;
    delete tmp;
}

void searchStack() {
    if (!stackTop) {
        cout << "Stack is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    StackNode *cur = stackTop;
    int posFromTop = 0;
    while (cur) {
        if (cur->data.bookID == id) {
            cout << "Book found at position " << 
            posFromTop << " from top of stack:\n";
            printBook(cur->data);
            return;
        }
        cur = cur->next;
        posFromTop++;
    }
    cout << "Book ID not found.\n";
}

void displayStack() {
    if (!stackTop) {
        cout << "Stack is empty!\n";
        return;
    }
    cout << "-- Stack of Books (Top to Bottom) --\n";
    StackNode *cur = stackTop;
    while (cur) {
        printBook(cur->data);
        cur = cur->next;
    }
}

// =============== 4. QUEUE ==================
struct QueueNode {
    Book data;
    QueueNode *next;
};
QueueNode *qFront = nullptr;
QueueNode *qRear = nullptr;

void enqueue() {
    Book b = inputBook();
    QueueNode *node = new QueueNode{b, nullptr};
    if (!qRear) {
        qFront = qRear = node;
    } else {
        qRear->next = node;
        qRear = node;
    }
    cout << "Book enqueued.\n";
}

void dequeue() {
    if (!qFront) {
        cout << "Queue is empty!\n";
        return;
    }
    QueueNode *tmp = qFront;
    cout << "Dequeued book:\n";
    printBook(tmp->data);
    qFront = qFront->next;
    if (!qFront) {
        qRear = nullptr;
    }
    delete tmp;
}

void searchQueue() {
    if (!qFront) {
        cout << "Queue is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    QueueNode *cur = qFront;
    int pos = 0;
    while (cur) {
        if (cur->data.bookID == id) {
            cout << "Found at position " 
            << pos << " from front:\n";
            printBook(cur->data);
            return;
        }
        cur = cur->next;
        pos++;
    }
    cout << "Book ID not found.\n";
}

void displayQueue() {
    if (!qFront) {
        cout << "Queue is empty!\n";
        return;
    }
    cout << "-- Queue (Front to Rear) --\n";
    QueueNode *cur = qFront;
    while (cur) {
        printBook(cur->data);
        cur = cur->next;
    }
}

// ======= 5. BINARY TREE (LINKED & ARRAY) ========
struct TreeNode {
    Book data;
    TreeNode *left;
    TreeNode *right;
};
TreeNode *treeRoot = nullptr;

Book treeArr[MAX];
bool treeArrUsed[MAX] = {false};

TreeNode* findMinNode(TreeNode *node) {
    while (node && node->left)
        node = node->left;
    return node;
}

TreeNode* insertBSTNode(TreeNode *node, Book b) {
    if (!node) {
        return new TreeNode{b, nullptr, nullptr};
    }
    if (b.bookID < node->data.bookID) {
        node->left = insertBSTNode(node->left, b);
    } else if (b.bookID > node->data.bookID) {
        node->right = insertBSTNode(node->right, b);
    } else {
        cout << "Book ID already exists in tree, skipping.\n";
    }
    return node;
}

void insertTreeLinked() {
    Book b = inputBook();
    treeRoot = insertBSTNode(treeRoot, b);
    cout << "Book inserted into binary tree (linked).\n";
}

void insertTreeArray() {
    Book b = inputBook();
    int i = 0;
    while (i < MAX) {
        if (!treeArrUsed[i]) {
            treeArr[i] = b;
            treeArrUsed[i] = true;
            cout << "Book inserted into binary tree (array) at index " << i << ".\n";
            return;
        }
        if (b.bookID == treeArr[i].bookID) {
            cout << "Book ID already exists in tree, skipping.\n";
            return;
        }
        i = (b.bookID < treeArr[i].bookID) ? (2 * i + 1) : (2 * i + 2);
    }
    cout << "Array-tree is full!\n";
}

void insertTree() {
    int choice;
    cout << "   Choose Tree Representation:\n";
    cout << "     1. Linked List\n";
    cout << "     2. Array\n";
    cout << "   Enter choice (1-2): ";
    cin >> choice;
    if (choice == 1) {
        insertTreeLinked();
    } else if (choice == 2) {
        insertTreeArray();
    } else {
        cout << "Invalid choice!\n";
    }
}

// ------------ TREE DELETE -------------
TreeNode* deleteBSTNode(TreeNode *node, int id, bool &found) {
    if (!node) return nullptr;
    if (id < node->data.bookID)
        node->left = deleteBSTNode(node->left, id, found);
    else if (id > node->data.bookID)
        node->right = deleteBSTNode(node->right, id, found);
    else {
        found = true;
        if (!node->left) {
            TreeNode *r = node->right;
            delete node;
            return r;
        }
        if (!node->right) {
            TreeNode *l = node->left;
            delete node;
            return l;
        }
        TreeNode *succ = findMinNode(node->right);
        node->data = succ->data;
        bool dummy = false;
        node->right = deleteBSTNode(node->right, succ->data.bookID, dummy);
    }
    return node;
}

void deleteTreeArray() {
    if (!treeArrUsed[0]) {
        cout << "Array-tree is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;
    int i = 0;
    while (i < MAX && treeArrUsed[i]) {
        if (treeArr[i].bookID == id) {
            treeArrUsed[i] = false;
            cout << "Book deleted from binary tree (array).\n";
            return;
        }
        i = (id < treeArr[i].bookID) ? (2 * i + 1) : (2 * i + 2);
    }
    cout << "Book ID not found.\n";
}

void deleteTree() {
    int choice;
    cout << "   Choose Tree Representation:\n";
    cout << "     1. Linked List\n";
    cout << "     2. Array\n";
    cout << "   Enter choice (1-2): ";
    cin >> choice;
    if (choice == 1) {
        if (!treeRoot) {
            cout << "Tree is empty!\n";
            return;
        }
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;
        bool found = false;
        treeRoot = deleteBSTNode(treeRoot, id, found);
        cout << (found ? "Book deleted from binary tree.\n" : "Book ID not found.\n");
    } else if (choice == 2) {
        deleteTreeArray();
    } else {
        cout << "Invalid choice!\n";
    }
}

// ------------ TREE SEARCH -------------
TreeNode* searchBSTNode(TreeNode *node, int id) {
    if (!node) return nullptr;
    if (node->data.bookID == id) return node;
    if (id < node->data.bookID)
        return searchBSTNode(node->left, id);
    return searchBSTNode(node->right, id);
}

void searchTreeArray() {
    if (!treeArrUsed[0]) {
        cout << "Array-tree is empty!\n";
        return;
    }
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    int i = 0;
    while (i < MAX && treeArrUsed[i]) {
        if (treeArr[i].bookID == id) {
            cout << "Found at index " << i << ":\n";
            printBook(treeArr[i]);
            return;
        }
        i = (id < treeArr[i].bookID) ? (2 * i + 1) : (2 * i + 2);
    }
    cout << "Book ID not found.\n";
}

void searchTree() {
    int choice;
    cout << "   Choose Tree Representation:\n";
    cout << "     1. Linked List\n";
    cout << "     2. Array\n";
    cout << "   Enter choice (1-2): ";
    cin >> choice;
    if (choice == 1) {
        if (!treeRoot) {
            cout << "Tree is empty!\n";
            return;
        }
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;
        TreeNode *res = searchBSTNode(treeRoot, id);
        if (res) {
            cout << "Book found:\n";
            printBook(res->data);
        } else {
            cout << "Book ID not found.\n";
        }
    } else if (choice == 2) {
        searchTreeArray();
    } else {
        cout << "Invalid choice!\n";
    }
}

// ---------- TREE DISPLAY -------------
void inorderDisplay(TreeNode *node) {
    if (!node) return;
    inorderDisplay(node->left);
    printBook(node->data);
    inorderDisplay(node->right);
}

void displayTreeArrayRec(int idx) {
    if (idx >= MAX || !treeArrUsed[idx]) return;
    displayTreeArrayRec(2 * idx + 1);
    printBook(treeArr[idx]);
    displayTreeArrayRec(2 * idx + 2);
}

void displayTreeArray() {
    if (!treeArrUsed[0]) {
        cout << "Array-tree is empty!\n";
        return;
    }
    cout << "-- Binary Tree (array representation, in-order) --\n";
    displayTreeArrayRec(0);
}

void displayTree() {
    int choice;
    cout << "   Choose Tree Representation:\n";
    cout << "     1. Linked List\n";
    cout << "     2. Array\n";
    cout << "   Enter choice (1-2): ";
    cin >> choice;
    if (choice == 1) {
        if (!treeRoot) {
            cout << "Tree is empty!\n";
            return;
        }
        cout << "-- Binary Tree (linked, in-order) --\n";
        inorderDisplay(treeRoot);
    } else if (choice == 2) {
        displayTreeArray();
    } else {
        cout << "Invalid choice!\n";
    }
}

// ========== MAIN MENU=============
int main() {
    int choice;
    char subChoice;

    while (true) {
        cout << "\n===== PERSONAL LIBRARY MANAGEMENT SYSTEM - MENU =====\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "=====================================================\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == 5) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        if (choice < 1 || choice > 5) {
            cout << "Invalid choice!\n";
            continue;
        }

        cout << "   a. Sorted Array\n";
        cout << "   b. Linked List\n";
        cout << "   c. Stack\n";
        cout << "   d. Queue\n";
        cout << "   e. Binary Tree (choose linked/array next)\n";
        cout << "Enter choice (a-e): ";
        cin >> subChoice;

        switch (choice) {
            case 1:
                if (subChoice == 'a') insertArray();
                else if (subChoice == 'b') insertList();
                else if (subChoice == 'c') pushStack();
                else if (subChoice == 'd') enqueue();
                else if (subChoice == 'e') insertTree();
                else cout << "Invalid choice!\n";
                break;
            case 2:
                if (subChoice == 'a') deleteArray();
                else if (subChoice == 'b') deleteList();
                else if (subChoice == 'c') popStack();
                else if (subChoice == 'd') dequeue();
                else if (subChoice == 'e') deleteTree();
                else cout << "Invalid choice!\n";
                break;
            case 3:
                if (subChoice == 'a') searchArray();
                else if (subChoice == 'b') searchList();
                else if (subChoice == 'c') searchStack();
                else if (subChoice == 'd') searchQueue();
                else if (subChoice == 'e') searchTree();
                else cout << "Invalid choice!\n";
                break;
            case 4:
                if (subChoice == 'a') displayArray();
                else if (subChoice == 'b') displayList();
                else if (subChoice == 'c') displayStack();
                else if (subChoice == 'd') displayQueue();
                else if (subChoice == 'e') displayTree();
                else cout << "Invalid choice!\n";
                break;
        }
    }
    return 0;
}