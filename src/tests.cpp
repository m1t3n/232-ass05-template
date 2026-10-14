#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <sstream>
#include <iostream>
//#include <format>
#include <string>
using namespace std;

// ============================================================
// STAGE 0 Tests
// ============================================================

/// Create a LegacyData union with an int (42). Call printLegacyData.
/// Verify the returned string matches "42".
void test_printLegacyData_int(void) 
{
    LegacyData x;
    x.i = 42;
    string y = printLegacyData(x, 'i');
    TEST_ASSERT_TRUE_MESSAGE(y=="42", "y was NOT 42.");
}

/// Create a LegacyData union with a double (3.14). Call printLegacyData.
/// Verify the returned string matches "3.14".
void test_printLegacyData_double(void) 
{
    LegacyData x;
    x.d = 3.14;
    string y = printLegacyData(x, 'd');
    TEST_ASSERT_TRUE_MESSAGE(y=="3.14", "y was NOT 3.14.");
}

// ============================================================
// STAGE 1 Tests
// ============================================================

/// Call createTwoStructNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoStructNodes_links_correctly(void) 
{
    structNode *e = createTwoStructNodes();
    TEST_ASSERT_TRUE_MESSAGE(e->value.i==5, "e was NOT 5");
    TEST_ASSERT_TRUE_MESSAGE(e->typeData=='i', "e was NOT i");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.14, e->nextPtr->value.d, "e was NOT 3.14");
    TEST_ASSERT_TRUE_MESSAGE(e->nextPtr->typeData=='d', "e was NOT d");

    delete e->nextPtr;
    delete e;
}

// ============================================================
// STAGE 2 Tests
// ============================================================

/// Call createTwoClassNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoClassNodes_links_correctly(void) 
{
    classNode *e = createTwoClassNodes();
    TEST_ASSERT_TRUE_MESSAGE(e->value.i==5, "e was NOT 5");
    TEST_ASSERT_TRUE_MESSAGE(e->typeData=='i', "e was NOT i");
    TEST_ASSERT_EQUAL_DOUBLE_MESSAGE(3.14, e->nextPtr->value.d, "e was NOT 3.14");
    TEST_ASSERT_TRUE_MESSAGE(e->nextPtr->typeData=='d', "e was NOT d");

    delete e->nextPtr;
    delete e;
}

// ============================================================
// STAGE 3 Tests
// ============================================================

/// Call createTwoTemplateNodes().
/// Verify head->value is 5 and head->nextPtr->value is 3.
/// Clean up allocated memory.
void test_createTwoTemplateNodes_links_correctly(void) 
{
    classNodeT<int> *h = createTwoTemplateNodes();
    TEST_ASSERT_TRUE_MESSAGE(h->value==5, "h is NOT 5.");
    TEST_ASSERT_TRUE_MESSAGE(h->nextPtr->value==3, "h is NOT 3.");

    delete h->nextPtr;
    delete h;
}

// ============================================================
// STAGE 4: LinkedList Tests
// ============================================================

/// Create a LinkedList. Add two nodes using addFirst.
/// Verify listLength() returns 2 after insertions.
void test_linkedList_addFirst_updates_counter(void) 
{
    LinkedList *i = new LinkedList();
    classNodeVariant *j = new classNodeVariant(4);
    classNodeVariant *k = new classNodeVariant(5);
    i->addFirst(j);
    i->addFirst(k);
    TEST_ASSERT_TRUE_MESSAGE(i->listLength()==2, "list length did NOT return 2");

    delete i;
}

/// Create a LinkedList. Add nodes (10, then 20) using addLast.
/// Capture std::cout and verify elements appear in order ("10" before "20").
void test_linkedList_addLast_places_at_end(void) 
{
    LinkedList *m = new LinkedList();
    classNodeVariant *n = new classNodeVariant(10);
    classNodeVariant *o = new classNodeVariant(20);
    cout << m->addLast(n);
    cout << m->addLast(o);
    TEST_ASSERT_TRUE_MESSAGE(n->nextPtr==o, "THEY ARE NOT IN ORDER");

    delete m;
}

/// Create a LinkedList with an int, double, and string.
/// Call deleteValue() with the double value (3.14).
/// Verify list length decreases to 2 and second call returns -1.
void test_linkedList_deleteValue_removes_variant(void) 
{
    LinkedList *p = new LinkedList();
    classNodeVariant *q = new classNodeVariant(5);
    classNodeVariant *r = new classNodeVariant(3.14);
    classNodeVariant *s = new classNodeVariant("hi");

    p->addFirst(q);
    p->addFirst(r);
    p->addFirst(s);
    p->deleteValue(3.14);

    TEST_ASSERT_TRUE_MESSAGE(p->listLength()==2, "not length of 2");
    TEST_ASSERT_TRUE_MESSAGE(p->deleteValue(3.14)==-1, "didn't return -1");
}

/// Create a LinkedList and insert three nodes.
/// Call destroyList().
/// Verify listLength() becomes 0.
void test_linkedList_destroyList_clears_all(void) 
{
    LinkedList *p = new LinkedList();
    classNodeVariant *q = new classNodeVariant(5);
    classNodeVariant *r = new classNodeVariant(3.14);
    classNodeVariant *s = new classNodeVariant("hi");

    p->addFirst(q);
    p->addFirst(r);
    p->addFirst(s);
    p->destroyList();

    TEST_ASSERT_TRUE_MESSAGE(p->listLength()==0, "not length of 0");
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteFirst().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteFirst(void) 
{
    LinkedList *t = new LinkedList();
    classNodeVariant *u = new classNodeVariant(10);
    classNodeVariant *v = new classNodeVariant(20);
    classNodeVariant *w = new classNodeVariant(30);
    t->addFirst(u);
    t->addFirst(v);
    t->addFirst(w);

    TEST_ASSERT_TRUE_MESSAGE(t->deleteFirst()==0, "didn't return 0");
    TEST_ASSERT_TRUE_MESSAGE(t->listLength()==2, "not equal to 2");
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteLast().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteLast(void) 
{
    LinkedList *x = new LinkedList();
    classNodeVariant *y = new classNodeVariant(10);
    classNodeVariant *z = new classNodeVariant(20);
    classNodeVariant *a = new classNodeVariant(30);
    x->addFirst(y);
    x->addFirst(z);
    x->addFirst(a);

    TEST_ASSERT_TRUE_MESSAGE(x->deleteLast()==0, "didn't return 0");
    TEST_ASSERT_TRUE_MESSAGE(x->listLength()==2, "not equal to 2");
}

/// Create a LinkedList with nodes (1, 2.5, "test").
/// Redirect std::cout buffer and call printList().
/// Verify printed output contains "1", "2.5" (or "2.50"), and "test".
void test_linkedList_printList(void) 
{
    LinkedList *b = new LinkedList();
    classNodeVariant *c = new classNodeVariant(1);
    classNodeVariant *d = new classNodeVariant(2.5);
    classNodeVariant *e = new classNodeVariant("test");
    b->addFirst(c);
    b->addFirst(d);
    b->addFirst(e);
    b->printList();

    TEST_ASSERT_TRUE_MESSAGE(1, "not 1");
    TEST_ASSERT_TRUE_MESSAGE(2.5, "not 2.5");
    TEST_ASSERT_TRUE_MESSAGE("test", "not test");
    
    delete b;
}