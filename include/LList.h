#ifndef LLIST_H
#define LLIST_H
#include <iostream>
template <typename T = int>
struct elem_link1
{
    T inf;
    elem_link1<T>* link;
};

template <typename T>
class LList
{
public:
    LList();
    LList(const LList&);
    LList& operator=(const LList&);
    ~LList();
    bool empty() const;
    void iterStart(elem_link1<T>* = NULL);
    elem_link1<T>* iter();
    void toEnd(const T&);
    void insertAfter(elem_link1<T>*, const T&);
    void insertBefore(elem_link1<T>*, const T&);
    void deleteAfter(elem_link1<T>*, T&);
    void deleteBefore(elem_link1<T>*, T&);
    void deleteElem(elem_link1<T>*, T&);
    void print() const;
    int length() const;
    void concat(const LList&);
    void reverse();

private:
    elem_link1<T>* start;
    elem_link1<T>* end;
    elem_link1<T>* current;
    void copyList(const LList&);
    void deleteList();
};

#endif // LLIST_H
