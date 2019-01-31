#include <iostream>
#include "LList.h"

using namespace std;

template <typename T>
void minimalList(LList<T> ll, T& minimal, LList<T>& newll)
{
    T x;
    ll.iterStart();
    ll.deleteElem(ll.iter(), minimal);
    while(!ll.empty())
    {
        ll.iterStart();
        ll.deleteElem(ll.iter(), x);
        if(x <= minimal)
        {
            newll.toEnd(minimal);
            minimal = x;
        }
        else newll.toEnd(x);
    }
}

template <typename T>
void sortList(LList<T> ll, LList<T>& newll)
{
    while(!ll.empty())
    {
        LList<T> ll2;
        T minimal;
        minimalList(ll, minimal, ll2);
        newll.toEnd(minimal);
        ll = ll2;
    }
}

template <typename T>
LList<T> mergeLists(LList<T> l1, LList<T> l2)
{
    LList<T> l3;
    T dummy;
    T x,y;
    l1.toEnd(dummy);
    l2.toEnd(dummy);
    l1.iterStart();
    l2.iterStart();
    l1.deleteElem(l1.iter(), x);
    l2.deleteElem(l2.iter(), y);
    while(!l1.empty() && !l1.empty())
    {
        if(x <= y)
        {
            l3.toEnd(x);
            l1.iterStart();
            l1.deleteElem(l1.iter(), x);
        }
        else
        {
            l3.toEnd(y);
            l2.iterStart();
            l2.deleteElem(l2.iter(), y);
        }
    }
    if(!l1.empty())
    {
        do
        {
            l3.toEnd(x);
            l1.iterStart();
            l1.deleteElem(l1.iter(), x);
        }
        while(x != dummy);
    }
    if(!l2.empty())
    {
        do
        {
            l3.toEnd(y);
            l2.iterStart();
            l2.deleteElem(l2.iter(), y);
        }
        while(y != dummy);
    }
    return l3;
}

int main()
{/*
    LList<int> ll;
    ll.toEnd(2);
    ll.toEnd(1);
    ll.iterStart();
    ll.insertAfter(ll.iter(), 6);
    ll.insertBefore(ll.iter(), 20);
    //ll.print();
    ll.iterStart();
    cout<<ll.length()<<endl;
    for(int i=0; i<2; i++)
    {
        ll.iter();
    }
    //ll.print();
    ll.insertAfter(ll.iter(),33);
    //ll.print();
    /*ll.iterStart();
    for(int i=0; i<3; i++)
    {
        ll.iter();
    }
    int x;
    ll.deleteAfter(ll.iter(),x);
    cout<<x;*/
    /*
    LList<int> newll;
    sortList(ll, newll);
    //newll.print();
    LList<int> ll2;
    ll2.toEnd(21);
    ll2.toEnd(42);
    ll2.toEnd(7);
    ll2.toEnd(14);
    LList<int> newll2;
    sortList(ll2, newll2);
    //newll2.print();
    //mergeLists(newll, newll2).print();*/
    return 0;
}
