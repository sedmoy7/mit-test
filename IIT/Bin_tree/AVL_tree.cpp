#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>

std::ifstream in("input.txt");

struct tree 
{
    int inf;
    tree* right;
    tree* left;
};

tree* node(int x) 
{
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    return n;
}

void create(tree*& tr, int n) 
{
    int x;
    if (n > 0) 
    {
        in >> x;
        tr = node(x);
        int nl = n / 2;
        int nr = n - nl - 1;
        create(tr->left, nl);
        create(tr->right, nr);
    }
}

void preorder(tree* tr) 
{
    if (tr) 
    {
        std::cout << tr->inf << " ";
        preorder(tr->left);
        preorder(tr->right);
    }
}

int lefth(tree* tr) 
{
    int k = 0;
    tree* x = tr;
    while (x) 
    {
        k++;
        x = x->left;
    }
    return k - 1;
}

int righth(tree* tr) 
{
    int k = 0;
    tree* x = tr;
    while (x) 
    {
        k++;
        x = x->right;
    }
    return k - 1;
}

void add(tree*& tr, int x) 
{
    tree* n = node(x);
    tree* y = tr;
    if (lefth(tr) == righth(tr)) 
    {
        do 
        {
            y = y->left;
        } while (y->left);
        if (!y->left) y->left = n;
        else y->right = n;
    }
    else {
        do 
        {
            y = y->right;
        } while (y->right);
        if (!y->left) y->left = n;
        else y->right = n;
    }
}

void find(tree* tr, int x, tree*& res) 
{
    if (tr) 
    {
        if (tr->inf == x) 
        {
            res = tr;
        }
        else 
        {
            find(tr->left, x, res);
            find(tr->right, x, res);
        }
    }
}

void del_n(tree* tr, int val)
{
    tree* y;
    find(tr, val, y);
    if (y) 
    {
        if (lefth(tr) == 0) tr = NULL;
        else if (lefth(tr) != righth(tr)) 
        {
            tree* x = tr->left;
            do 
            {
                x = x->left;
            } while (x->left->left);

            if (x->right) 
            {
                if (x->right->inf == val) 
                {
                    x->right = NULL;
                }
                else 
                {
                    y->inf = x->right->inf;
                    x->right = NULL;
                }
                delete x->right;
            }
            else 
            {
                if (x->left->inf == val) 
                {
                    x->left = NULL;
                }
                else 
                {
                    y->inf = x->left->inf;
                    x->left = NULL;
                }
                delete x->left;
            }
        }
        else 
        {
            tree* x = tr->right;
            do 
            {
                x = x->right;
            } while (x->right->right);

            if (x->right) 
            {
                if (x->right->inf == val) 
                {
                    x->right = NULL;
                }
                else 
                {
                    y->inf = x->right->inf;
                    x->right = NULL;
                }
                delete x->right;
            }
            else 
            {
                if (x->left->inf == val) 
                {
                    x->left = NULL;
                }
                else 
                {
                    y->inf = x->left->inf;
                    x->left = NULL;
                }
                delete x->left;
            }
        }
    }
}

void print(tree* tr, int k) 
{
    if (!tr) std::cout << "Empty tree\n";
    else 
    {
        std::queue<tree*> cur, next;
        tree* r = tr;
        cur.push(r);
        int j = 0;
        while (cur.size()) 
        {
            if (j == 0)
            {
                for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
                    std::cout << ' ';
            }
            tree* buf = cur.front();
            cur.pop();
            j++;
            if (buf) 
            {
                std::cout << buf->inf;
                next.push(buf->left);
                next.push(buf->right);
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    std::cout << ' ';
            }
            else 
            {
                for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
                    std::cout << ' ';
                std::cout << ' ';
            }
            if (cur.empty()) 
            {
                std::cout << std::endl;
                swap(cur, next);
                j = 0;
                k--;
            }
        }
    }
}

void print_leaves(tree* tr)
{
    if (tr == NULL) return;
    if (tr->left == NULL && tr->right == NULL)
    {
        std::cout << tr->inf << " ";
        return;
    }
    print_leaves(tr->left);
    print_leaves(tr->right);
}

int main() 
{
    tree* tr = NULL;
    int n, x;
    in >> n;

    create(tr, n);

    int k = int(log((float)n) / log((float)2.0));

    print(tr, k);
    //preorder(tr);
    std::cout << "\nLeaves: ";
    print_leaves(tr);

    /*
    std::cout << lefth(tr) << " " << righth(tr);
    std::cout << std::endl;

    std::cout << "x = ";
    std::cin >> x;
    add(tr, x);
    n++;

    k = int(log((float)n) / log((float)2.0));

    print(tr, k);
    preorder(tr);
    */
    /*
    std::cout << std::endl;
    std::cout << " del node: ";
    std::cin >> x;
    del_n(tr, x);

    n--;
    k = int(log((float)n) / log((float)2.0));
    print(tr, k);
    preorder(tr);

    std::cout << std::endl;
    */
    return 0;
}
