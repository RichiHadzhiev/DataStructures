#include <iostream>
#include <cstdlib>
#include <cassert>
#include <queue>
using namespace std;

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

template <typename T>
class Graph
{
    public:
        void addTop(const T&);
        void deleteTop(const T&);
        void addRib(const T&, const T&);
        void deleteRib(const T&, const T&);
        bool top(const T&);
        bool rib(const T&, const T&);
        bool empty() const;
        elem_link1<T>* point(const T&);
        LList<T> vertexes();
        void print();
    private:
        LList< LList<T> > g;
};

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
        ll.toEnd(q->inf);
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

template <typename T>
void create_graph(Graph<T>& g)
{
    char c;
    do
    {
        cout<<"Add top:\n";
        T x;
        cin>>x;
        g.addTop(x);
        cout<<"One more y/n?\n";
        cin>>c;
    } while(c == 'y');
    cout<<"Ribs:\n";
    do
    {
        cout<<"Start top: ";
        T x;
        cin>>x;
        cout<<"End top: ";
        T y;
        cin>>y;
        g.addRib(x, y);
        cout<<"One more y/n?\n";
        cin>>c;
    } while(c == 'y');
}

template <typename T>
bool member(const T& a, LList<T>& l)
{
    l.iterStart();
    elem_link1<T> *p = l.iter();
    while(p && p->inf != a)
        p = p->link;
    return p!=NULL;
}

template <typename T>
void BFS(const T& a, Graph<T>& g, LList<T>& l)
{
    queue<int> q;
    q.push(a);
    l.toEnd(a);
    while(!q.empty())
    {
        T x = q.front();
        q.pop();
        cout<<x<<" ";
        elem_link1<T>* p = g.point(x);
        p = p->link;
        while(p)
        {
            if(!member(p->inf, l))
            {
                q.push(p->inf);
                l.toEnd(p->inf);
            }
            p = p->link;
        }
    }
}

template <typename T>
LList<T> differenceSets(LList<T>& l1, LList<T>& l2)
{
    LList<T> dif;
    l1.iterStart();
    l2.iterStart();
    elem_link1<T> *iter1 = l1.iter();
    elem_link1<T> *iter2 = l2.iter();
    while(iter1)
    {
        if(!member(iter1->inf, l2))
            dif.toEnd(iter1->inf);
        iter1 = iter1->link;
    }
    return dif;
}

template <typename T>
void full_BFS(Graph<T>& g)
{
    LList<T> v = g.vertexes(),
                 l,
                 h = v;
    while(!h.empty())
    {
        h.iterStart();
        elem_link1<T> *p = h.iter();
        BFS(p->inf, g, l);
        h = differenceSets(v, l);
    }
}

template <typename T>
void DFS(const T& a, Graph<T>& g, LList<T>& l)
{
    l.toEnd(a);
    cout<<a<<" ";
    elem_link1<T> *p = g.point(a);
    p = p->link;
    while(p)
    {
        if(!member(p->inf, l))
            DFS(p->inf, g, l);
        p = p->link;
    }
}

template <typename T>
void full_DFS(Graph<T>& g)
{
    LList<T> v = g.vertexes(),
                l,
                h = v;
    while(!h.empty())
    {
        h.iterStart();
        elem_link1<T> *p = h.iter();
        DFS(p->inf, g, l);
        h = differenceSets(v, l);
    }
}

template <typename T>
bool way(const T& a, const T& b, Graph<T>& g, LList<T>& l)
{
    l.toEnd(a);
    if(a == b)
        return true;
    elem_link1<T> *p = g.point(a);
    p = p->link;
    while(p)
    {
        if(!member(p->inf, l))
        {
            if(way(p->inf, b, g, l)) return true;
            deleteLast(l);
        }
        p = p->link;
    }
}

template <typename T>
void deleteLast(LList<T>& l)
{
    l.iterStart();
    T x;
    elem_link1<T> *p = l.iter();
    while(p->link)
    {
        p = p->link;
    }
    l.deleteElem(p, x);
}

bool flag = false;
template <typename T>
void allways(const T& a, const T& b, Graph<T>& g, LList<T>& l)
{
    l.toEnd(a);
    if(a == b)
    {
        flag = true;
        l.print();
    }
    else
    {
        elem_link1<T> *p = g.point(a);
        p = p->link;
        while(p)
        {
            if(!member(p->inf, l))
            {
                allways(p->inf, b, g, l);
                deleteLast(l);
            }
            p = p->link;
        }
    }
}

//bool flag = false;
int minlen = 5;
template <typename T>
void minway(const T& a, const T& b, Graph<T>& g, LList<T>& l, LList<T>& minPath)
{
    l.toEnd(a);
    if(a == b)
    {
        flag = true;
        int len = l.length();
        if(len < minlen)
        {
            minlen = len;
            minPath = l;
        }
    }
    else
    {
        elem_link1<T> *p = g.point(a);
        p = p->link;
        while(p)
        {
            if(!member(p->inf, l))
            {
                minway(p->inf, b, g, l, minPath);
                deleteLast(l);
            }
            p = p->link;
        }
    }
}

int main()
{
    /*
    LList<int> a;
    a.toEnd(3);
    a.toEnd(4);
    a.toEnd(2);
    a.print();
    */
    Graph<int> g;
    g.addTop(1);
    g.addTop(4);
    g.addTop(2);
    g.addTop(3);
    g.addRib(1,4);
    g.addRib(4,2);
    g.addRib(2,1);
    g.addRib(3,1);
    g.addRib(3,4);

    //cout<<"Creating your own graph\n";
    //Graph<int> g1;
    //create_graph(g1);
    //g1.print();

    //cout<<"Now the BFS\n";
    //LList<int> b;
    //int vertex;
    //cout<<"Choose vertex to start from: ";
    //cin>>vertex;
    //BFS(vertex, g1, b);

    /*
    cout<<"Now the DFS\n";
    LList<int> b;
    int vertex;
    cout<<"Choose vertex to start from: ";
    cin>>vertex;
    DFS(vertex, g, b);
    cout<<endl;
    cout<<"Now the full DFS\n";
    full_DFS(g);
    cout<<endl;
    */

    cout<<"Insert 2 vertices to check if there is a way\n";
    int x; cout<<"x="; cin>>x;
    int y; cout<<"y="; cin>>y;
    LList<int> c;
    LList<int> minPath;
    /*
    if(way(x, y, g, c))
    {
        cout<<"There is a way between "<<x<<" and "<<y<<" and it is the following:\n";
        c.print();
    }
    else cout<<"There is NO way between "<<x<<" and "<<y<<".\n";
    */

    //allways(x, y, g, c);
    minway(x, y, g, c, minPath);
    minPath.print();
}
