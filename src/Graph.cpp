#include "Graph.h"

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

void Graph<T>::addRib(const T& a, const T& b)
{
    g.iterStart();
    elem_link1< LList<T > *p;
    elem_link1<T> *q;
    do
    {
        p = g.iter();
        p->inf.iterStart();
        q = p->inf.iter();
    } while(q->inf != a);
    p->inf.toEnd(b);
}
