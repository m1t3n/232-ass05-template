// ============================================================
// CSCI 232 Assignment 05 – Evolution of Data Structures
// Student Implementation
// ============================================================
// ============================================================

#include "code.hpp"
#include <iostream>
#include <format>
#include <string> //using == to make comparison between strings
using namespace std;

string AUTHOR_NAME       = "Mikayla Iten";
string AUTHOR_AUTHORSHIP = "I declare that I am the author of this work, take full responsibility for it, and have disclosed any material external assistance.";

// ============================================================
// STAGE 0: Legacy C Union
// ============================================================

/// Converts a LegacyData union to a formatted string.
/// Format specs:
/// 'i' -> integer value as string (e.g., "42")
/// 'd' -> double value formatted to 2 decimal places (e.g., "3.14")
/// 'c' -> string pointer content (or "nullptr" if cPtr is null)
/// default -> "unknown"

string printLegacyData(LegacyData data, char type) {
    // Implement switch/case for 'i', 'd', 'c' and default case
    string result = "unknown";
   if (type == 'i'){
        result = format("{}", data.i);
        return result;
   }
    if (type == 'c'){
        if (data.cPtr != NULL){
            result = format("{}", data.cPtr);
        }
        return result;
    }
    if (type == 'd'){
        result = format("{}", data.d);
        return result;
    }
    return "unknown";
}


// ============================================================
// STAGE 1: C-Style Struct
// ============================================================

/// Initializes a structNode with value, type indicator, and nullptr nextPtr.
void initStructNode(structNode* nPtr, LegacyData val, char type) {
    nPtr->value = val;
    nPtr->nextPtr = NULL;
    nPtr->typeData = type;
}

/// Dynamically allocates two structNodes.
/// Node 1: int 5 ('i')
/// Node 2: double 3.14 ('d')
/// Links Node 1 -> Node 2 -> nullptr
/// Returns pointer to Node 1.
structNode* createTwoStructNodes() {
    structNode *a = new structNode;
    LegacyData c;
    c.i = 5;
    initStructNode(a, c, 'i');

    structNode *b = new structNode;
    LegacyData d;
    d.d = 3.14;
    initStructNode(b, d, 'd');

    a->nextPtr = b;

    return a;
}

// ============================================================
// STAGE 2: Early C++ Class (Classic Constructor)
// ============================================================

/// Constructor: Assign fields inside curly braces.
/// DO NOT use member initializer lists here!

// uncomment the following code to implement the classNode constructor

classNode::classNode(LegacyData val, char type) {
    if (type == 'i')
        value.i = val.i; 
    if (type == 'c')
        value.cPtr = val.cPtr;
    if (type == 'd')
        value.d = val.d;
    typeData = type;
    nextPtr = NULL;
    }
 
/// Dynamically allocates two classNodes (int 5, double 3.14) and links them.
classNode* createTwoClassNodes() {

    LegacyData x;
    x.i = 5;
    classNode *a = new classNode(x,'i');

    LegacyData y;
    y.d = 3.14;
    classNode *b = new classNode(y, 'd');

    a->nextPtr = b;
    return a;
}

// ============================================================
// STAGE 3: C++98 Templates
// ============================================================

/// Dynamically allocates two classNodeT<int> objects (int 5, int 3) and links them.
classNodeT<int>* createTwoTemplateNodes() {
    
    classNodeT<int> *f = new classNodeT<int>(5);
    classNodeT<int> *g = new classNodeT<int>(3);
    f->nextPtr = g;
    return f;
}

// ============================================================
// STAGE 4: C++17 Variant and LinkedList Manager
// ============================================================

// uncomment the following code to implement the LinkedList methods

LinkedList::LinkedList() {
    // Initialize headPtr to nullptr and counter to 0
    headPtr = NULL;
    counter = 0;
}

LinkedList::~LinkedList() {
    // Clean up memory by calling destroyList()
    destroyList();
}


void LinkedList::destroyList() {
    // Iterate through list, delete all nodes, and reset counter to 0
    if (headPtr == NULL){
        return;
    }

    while (headPtr != NULL){
        classNodeVariant *temp = headPtr->nextPtr;
        delete headPtr;
        headPtr = temp;
    }
    counter = 0;
    
}

int LinkedList::addFirst(classNodeVariant* newNodePtr) {

    if (newNodePtr == NULL){
        return -1;
    }

    newNodePtr->nextPtr = headPtr;
    headPtr = newNodePtr;
    counter++;

    // Prepend node to the front of list, increment counter
    // Return -1 if newNodePtr is nullptr, 0 on success
    return 0;
}

int LinkedList::addLast(classNodeVariant* newNodePtr) {
    // TODO: Append node to the end of list, increment counter
    // Return -1 if newNodePtr is nullptr, 0 on success
    if (newNodePtr == NULL){
        return -1;
    }
    if (headPtr == NULL){
        return addFirst(newNodePtr); //if it's empty last=first
    }

    classNodeVariant *currentPtr = headPtr;
    while (currentPtr != NULL && currentPtr->nextPtr != NULL){
        currentPtr = currentPtr->nextPtr;
    }
    currentPtr->nextPtr = newNodePtr;
    counter++;
    return 0;
}

int LinkedList::deleteFirst() {
    // Delete first node, update headPtr, decrement counter
    // Return -1 if list is empty, 0 on success
    if (headPtr==NULL){
        return -1;
    }

    classNodeVariant *temp = headPtr->nextPtr;
    delete headPtr;
    headPtr = temp;

    counter--;
    return 0;
}

int LinkedList::deleteLast() {
    if (headPtr == NULL) {
        return -1;
    }
    // If there is only 1 node in the list
    if (headPtr->nextPtr == NULL) {
        delete headPtr;
        headPtr = NULL;
        counter--;
        return 0;
    }

    classNodeVariant *current = headPtr;
    while (current->nextPtr->nextPtr != NULL) {
        current = current->nextPtr;
    }
    delete current->nextPtr;
    current->nextPtr = NULL;
    counter--;
    return 0;
}


int LinkedList::deleteValue(ModernData targetValue) {

    if (headPtr == NULL) {
        return -1;
    }
    // node=value
    if (headPtr->value == targetValue) {
        classNodeVariant *temp = headPtr->nextPtr;
        delete headPtr;
        headPtr = temp;
        counter--;
        return 0;
        }


    classNodeVariant *a = headPtr;
    classNodeVariant *b = a->nextPtr;

    while (b != NULL && b->value != targetValue) {
        a = b;
        b = b->nextPtr;
    }

    if (b != NULL && b->value == targetValue) {
        a->nextPtr = b->nextPtr;
        delete b;
        counter--;
        return 0;
    }
    return -1;

}


int LinkedList::printList() {
    // Iterate through list and print each variant value to std::cout
    // Use std::holds_alternative or std::get
    // Return -1 if list is empty, 0 on success
    if (headPtr == NULL){
        return -1;
    }

    classNodeVariant *curr = headPtr;
    while (curr != NULL){
        if (holds_alternative<int>(curr->value)){
            cout << get<int>(curr->value);
        }
        else if (holds_alternative<string>(curr->value)){
            cout << get<string>(curr->value);
        }
        else if (holds_alternative<double>(curr->value)){
            cout << get<double>(curr->value);
        }
        curr = curr->nextPtr;
    }
    return 0;
}

int LinkedList::listLength() {
    // Return node count
    return counter;
}

//i used google ai to explain std::holds_alternative and std::get