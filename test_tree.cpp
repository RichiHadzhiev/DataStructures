#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct node
{
    T inf;
    node* left;
    node* right;
};

template <typename T>
class Tree
{
public:
    Tree();
    Tree(const Tree&);
    Tree& operator=(const Tree&);
    ~Tree();

    bool empty() const;
    node<T>* getRoot() const;
    T rootTree() const;
    Tree leftTree() const;
    Tree rightTree() const;
    void create3(const T&, const Tree<T>&, const Tree<T>&);
    void print() const
    {
        pr(root);
        cout<<endl;
    }
    void create()
    {
        createTree(root);
    }
private:
    node<T>* root;
    void copyTree(const Tree<T>&);
    void copy(node<T>*&, node<T>* const &) const;
    void deleteTree(node<T>*&) const;
    void pr(const node<T>*) const;
    void createTree(node<T>*&) const;
};

template <typename T>
Tree<T>::Tree()
{
    root = NULL;
}

template <typename T>
Tree<T>::~Tree()
{
    deleteTree(root);
}

template <typename T>
Tree<T>::Tree(const Tree<T>& other)
{
    copyTree(other);
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other)
{
    if(this != &other)
    {
        deleteTree(root);
        copyTree(other);
    }
    return *this;
}

template <typename T>
void Tree<T>::copyTree(const Tree<T>& other)
{
    copy(root, other.root);
}

template <typename T>
void Tree<T>::copy(node<T>*& pos, node<T>* const & r) const
{
    pos = NULL;
    if(r)
    {
        pos = new node<T>;
        assert(pos != NULL);
        pos->inf = r->inf;
        copy(pos->left, r->left);
        copy(pos->right, r->right);
    }
}

template <typename T>
void Tree<T>::deleteTree(node<T>*& p) const
{
    if(p)
    {
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
        p = NULL;
    }
}

template <typename T>
bool Tree<T>::empty() const
{
    return root == NULL;
}

template <typename T>
node<T>* Tree<T>::getRoot() const
{
    return root;
}

template <typename T>
T Tree<T>::rootTree() const
{
    return root->inf;
}

template <typename T>
Tree<T> Tree<T>::leftTree() const
{
    Tree<T> t;
    copy(t.root, root->left);
    return t;
}

template <typename T>
Tree<T> Tree<T>::rightTree() const
{
    Tree <T> t;
    copy(t.root, root->right);
    return t;
}

template <typename T>
void Tree<T>::pr(const node<T>* p) const
{
    if(p)
    {
        pr(p->left);
        cout<<p->inf<<" ";
        pr(p->right);
    }
}

template <typename T>
void Tree<T>::create3(const T& x, const Tree<T>& l, const Tree<T>& r)
{
    if(root)
        deleteTree(root);
    root = new node<T>;
    assert(root != NULL);
    root->inf = x;
    copy(root->left, l.root);
    copy(root->right, r.root);
}

template <typename T>
void Tree<T>::createTree(node<T>* & pos) const
{
    T x;
    char c;
    cout<<"Root: ";
    cin>>x;
    pos = new node<T>;
    assert(pos != NULL);
    pos->inf = x;
    pos->left = NULL;
    pos->right = NULL;
    cout<<"Left tree of: "<<x<<" y/n?\n";
    cin>>c;
    if(c == 'y')
        createTree(pos->left);
    cout<<"Right tree of: "<<x<<" y/n?\n";
    cin>>c;
    if(c == 'y')
        createTree(pos->right);
}

template <typename T>
int depth(const Tree<T> t)
{
    if(t.empty())
        return 0;
    int n, m;
    n = depth(t.leftTree());
    m = depth(t.rightTree());
    if(n > m)
        return n+1;
    else return m+1;
}

typedef Tree<int> intTree;
int main()
{
    intTree t;
    t.create();
    t.print();
    cout<<"Root: "<<t.rootTree()<<endl;
    intTree t1 = t.leftTree();
    intTree t2 = t.rightTree();
    cout<<"Left: ";
    t1.print();
    cout<<"Right: ";
    t2.print();
    intTree t3;
    t3.create3(t.rootTree(), t2, t1);
    t3.print();
    cout<<depth(t);
}


