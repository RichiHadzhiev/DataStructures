#include "LList.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template <typename T>
LList<T>::LList()
{
    start = end = NULL;
}
template <typename T>
LList<T>::~LList()
{
    deleteList();
}
template <typename T>
LList<T>::LList(const LList<T>& r)
{
    copyList(r);
}

template <typename T>
LList<T>& LList<T>::operator=(const LList<T>& r)
{
    if (this != &r)
    {
        deleteList();
        copyList(r);
    }
    return *this;
}

template <typename T>
void LList<T>::copyList(const LList<T>& r)
{
    start = end = NULL;
    elem_link1<T> *p = r.start;
    while (p)
    {
        toEnd(p->inf);
        p = p->link;
    }
}

template <typename T>
void LList<T>::deleteList()
{
    elem_link1<T> *p;
    while (start)
    {
        p = start;
        start = start->link;
        delete p;
    }
    end = NULL;
}

template <typename T>
void LList<T>::iterStart(elem_link1<T> *p)
{
    if (p) current = p;
    else current = start;
}

template <typename T>
elem_link1<T>* LList<T>::iter()
{
    elem_link1<T> *p = current;
    if (current) current = current->link;
    return p;
}

template <typename T>
void LList<T>::toEnd(const T& x)
{
    elem_link1<T>* p = end;
    end = new elem_link1<T>;
    assert(end != NULL);
    end->inf = x;
    end->link = NULL;
    if (p) p->link = end;
    else start = end;
}

template <typename T>
void LList<T>::insertAfter(elem_link1<T>* p, const T& x)
{
    elem_link1<T> *q = new elem_link1<T>;
    assert(q != NULL);
    q->inf = x;
    q->link = p->link;
    if (p == end) end = q;
    p->link = q;
}

template <typename T>
void LList<T>::insertBefore(elem_link1<T>* p, const T& x)
{
    elem_link1<T>* q = new elem_link1<T>;
    assert(q != NULL);
    *q = *p;
    if (p == end) end = q;
    p->inf = x;
    p->link = q;
}

template <typename T>
void LList<T>::deleteAfter(elem_link1<T>* p, T& x)
{
    if (p->link)
    {
        elem_link1<T>* q = p->link;
        x = q->inf;
        p->link = q->link;
        if (q == end) end = p;
        delete q;
    }
    else
    {
        cout << "There is not an element after p.\n";
        exit(1);
    }
}

template <typename T>
void LList<T>::deleteElem(elem_link1<T>* p, T& x)
{
    if (p == start)
    {
        x = p->inf;
        if (start == end)
        {
             start = end = NULL;
        }
        else start = start->link;
        delete p;
    }
    else
    {
         elem_link1<T>* q = start;
         while (q->link != p) q = q->link;
         deleteAfter(q, x);
    }
}

template <typename T>
void LList<T>::deleteBefore(elem_link1<T>* p, T& x)
{
     if (p != start)
     {
        elem_link1<T>* q = start;
        while (q->link != p) q = q->link;
        deleteElem(q, x);
     }
     else
     {
         cout << "There is not an element before p.\n";
         exit(1);
     }
}

template <typename T>
bool LList<T>::empty() const
{
    return start == NULL;
}

template <typename T>
void LList<T>::print() const
{
    elem_link1<T> *p = start;
    while (p)
    {
        cout << p->inf << " ";
        p = p->link;
    }
    cout << endl;
}

template <typename T>
int LList<T>::length() const
{
    int n = 0;
    elem_link1<T> *p = start;
    while (p)
    {
        n++;
        p = p->link;
    }
    return n;
}

template <typename T>
void LList<T>::concat(const LList<T>& r)
{
    elem_link1<T> *p = r.start;
    while (p)
    {
        toEnd(p->inf);
        p = p->link;
    }
}

template <typename T>
void LList<T>::reverse()
{
    LList<T> r;
    elem_link1<T>* p = start;
    if (p)
    {
         r.toEnd(p->inf);
         p = p->link;
         while (p)
         {
             r.insertBefore(r.start, p->inf);
             p = p->link;
         }
    }
    *this = r;
}

template class LList<int>;
//template class LList< LList<int> >;
