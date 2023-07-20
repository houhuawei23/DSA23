#include <bits/stdc++.h>

using namespace std;

class LeftistHeap
{
private:
    struct LeftistNode
    {
        int element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const int &e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int npl = 0)
            : element(e), left(lt), right(rt), npl(npl) {}
    };

    LeftistNode *root;
    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2);
    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2);
    void swapChildren(LeftistNode *t);
    void reclaimMemory(LeftistNode *t);
    LeftistNode *clone(LeftistNode *t) const;

public:
    LeftistHeap();                       // constructor
    LeftistHeap(const LeftistHeap &rhs); // copy constructor
    ~LeftistHeap();                      // destructor
    bool isEmpty() const;                // return true if empty, false otherwise
    const int &findMin() const;          // return reference to the minimum item
    void insert(const int &x);           // insert x
    void deleteMin();                    // delete minimum item
    void deleteMin(int &minItem);        // delete minimum item and return it
    void makeEmpty();                    // make the heap empty
    void merge(LeftistHeap &rhs);        // merge rhs into the priority queue

    const LeftistHeap &operator=(const LeftistHeap &rhs);
};

// public member functions
LeftistHeap::LeftistHeap()
{
    root = nullptr;
}

LeftistHeap::LeftistHeap(const LeftistHeap &rhs)
{
    root = nullptr;
    *this = rhs;
}

LeftistHeap::~LeftistHeap()
{
    makeEmpty();
}

bool LeftistHeap::isEmpty() const
{
    return root == nullptr;
}

const int &LeftistHeap::findMin() const
{
    return root->element;
}

void LeftistHeap::insert(const int &x)
{
    root = merge(new LeftistNode(x), root);
}

void LeftistHeap::deleteMin()
{
    if (isEmpty())
        throw "deleteMin error: heap is empty";
    LeftistNode *oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;
}

void LeftistHeap::deleteMin(int &minItem)
{
    if (isEmpty())
        throw "deleteMin error: heap is empty";
    minItem = root->element;
    LeftistNode *oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;
}

void LeftistHeap::makeEmpty()
{
    reclaimMemory(root);
    root = nullptr;
}

void LeftistHeap::merge(LeftistHeap &rhs)
{
    if (this == &rhs)
        return;
    root = merge(root, rhs.root);
    rhs.root = nullptr;
}

const LeftistHeap &LeftistHeap::operator=(const LeftistHeap &rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}
/// private member functions

LeftistHeap::LeftistNode *LeftistHeap::merge(LeftistNode *h1, LeftistNode *h2)
{
    if (h1 == nullptr)
        return h2;
    if (h2 == nullptr)
        return h1;
    // h1 has the smaller root
    if (h1->element < h2->element)
        return merge1(h1, h2);
    else
        return merge1(h2, h1);
}

LeftistHeap::LeftistNode *LeftistHeap::merge1(LeftistNode *h1, LeftistNode *h2)
{
    // h1 is the single node
    if (h1->left == nullptr)
        h1->left = h2;
    // else merge the right subtree of h1 with h2
    else
    {
        h1->right = merge(h1->right, h2);
        if (h1->left->npl < h1->right->npl)
            swapChildren(h1);
        h1->npl = h1->right->npl + 1;
    }
    return h1;
}

void LeftistHeap::swapChildren(LeftistNode *t)
{
    LeftistNode *tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}

void LeftistHeap::reclaimMemory(LeftistNode *t)
{
    if (t != nullptr)
    {
        reclaimMemory(t->left);
        reclaimMemory(t->right);
        delete t;
    }
}

LeftistHeap::LeftistNode *LeftistHeap::clone(LeftistNode *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
}

int main()
{
    LeftistHeap h;
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        int tmp;
        cin >> tmp;
        h.insert(tmp);
    }

    while (h.isEmpty() == false)
    {
        int min;
        h.deleteMin(min);
        cout << min << " ";
        // int a, b;
        // h.deleteMin(a);
        // h.deleteMin(b);

        // ans += a + b;
        // h.insert(a + b);
        // cout << a + b << " ";
    }
    return 0;
}