#include "Graph.h"
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
void Graph<T>::addTop(const T& a)
{
    LList<T> l;
    l.toEnd(a);
    g.toEnd(l);
}

template <typename T>
void Graph<T>::deleteTop(const T& a)
{
    //delete all the ribs from random vertex to vertex "a"
    g.iterStart();
    elem_link1< LList<T> > *p = g.iter(), *r;
    while(p)
    {
        p->inf.iterStart();
        elem_link1<T> *q = p->inf.iter();
        if(rib(q->inf, a))
            deleteRib(q->inf, a);
        p = p->link;
    }
    //delete the list, implementing the vertex "a" and all its successors
    g.iterStart();
    elem_link1<T> *q;
    do
    {
        r = g.iter();
        r->inf.iterStart();
        q = r->inf.iter();
    } while(q->inf != a);
    LList<T> x;
    g.deleteElem(r, x);
}

template <typename T>
void Graph<T>::addRib(const T& a, const T& b)
{
    g.iterStart();
    elem_link1< LList<T> > *p;
    elem_link1<T> *q;
    do
    {
        p = g.iter();
        p->inf.iterStart();
        q = p->inf.iter();
    } while(q->inf != a);
    p->inf.toEnd(b);
}

template <typename T>
void Graph<T>::deleteRib(const T& a, const T& b)
{
    g.iterStart();
    elem_link1< LList<T> > *p;
    elem_link1<T> *q;
    do
    {
        p = g.iter();
        p->inf.iterStart();
        q = p->inf.iter();
    } while(q->inf != a);
    q = q->link;
    while(q->inf != b)
        q = q->link;
    T x;
    p->inf.deleteElem(q, x);
}

template <typename T>
bool Graph<T>::top(const T& a)
{
    g.iterStart();
    elem_link1< LList<T> > *p;
    elem_link1<T> *q;
    do
    {
        p = g.iter();
        p->inf.iterStart();
        q = p->inf.iterStart();
    } while(q->inf != a && p);
    return q->inf == a;
}

template <typename T>
bool Graph<T>::rib(const T& a, const T& b)
{
    elem_link1<T> *p = point(a);
    p = p->link;
    while(p && p->inf != b)
        p = p->link;
    return p != NULL;
}

template <typename T>
bool Graph<T>::empty() const
{
    return g.empty();
}

template <typename T>
elem_link1<T>* Graph<T>::point(const T& a)
{
    g.iterStart();
    elem_link1< LList<T> > *p;
    elem_link1<T> *q;
    do
    {
        p = g.iter();
        p->inf.iterStart();
        q = p->inf.iter();
    } while(q->inf != a);
    return q;
}

template <typename T>
LList<T> Graph<T>::vertexes()
{
    LList<T> ll;
    g.iterStart();
    elem_link1< LList<T> > *p = g.iter();
    while(p)
    {
        p->inf.iterStart();
        elem_link1<T> *q = p->inf.iter();
        ll.toEnd(q);
        p = p->link;
    }
    return ll;
}

template <typename T>
void Graph<T>::print()
{
    g.iterStart();
    elem_link1< LList<T> > *p = g.iter();
    while(p)
    {
        p->inf.print();
        p = p->link;
    }
    cout<<endl;
}
