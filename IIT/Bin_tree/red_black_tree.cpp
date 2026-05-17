#include <iostream>

enum Color { RED, BLACK };

struct tree 
{
    int inf;
    Color color;
    tree* right;
    tree* left;
    tree* parent;
};

tree* node(tree* p, int x) 
{
    tree* n = new tree;
    n->inf = x;
    n->color = RED;
    n->left = n->right = NULL;
    n->parent = p;
    return n;
}

tree* root(int x) 
{
    tree* n = new tree;
    n->inf = x;
    n->color = BLACK;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

tree* grandparent(tree* x) 
{
    if (x != NULL && x->parent != NULL)
        return x->parent->parent;
    return NULL;
}

tree* uncle(tree* x) 
{
    tree* g = grandparent(x);
    if (g == NULL) return NULL;
    if (x->parent == g->left) return g->right;
    else return g->left;
}

tree* sibling(tree* x) 
{
    if (x != NULL && x->parent != NULL) 
    {
        if (x == x->parent->left) return x->parent->right;
        else return x->parent->left;
    }
    return NULL;
}

void rotate_left(tree*& tr, tree* x)
{
    tree* y = x->right;
    x->right = y->left;

    if (y->left != NULL) y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == NULL) tr = y;
    else if (x == x->parent->left) x->parent->left = y; 
    else x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void rotate_right(tree*& tr, tree* x) 
{
    tree* y = x->left;
    x->left = y->right;
    if (y->right != NULL) y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) tr = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void insert_case1(tree*& tr, tree* x);
void insert_case2(tree*& tr, tree* x);
void insert_case3(tree*& tr, tree* x);
void insert_case4(tree*& tr, tree* x);
void insert_case5(tree*& tr, tree* x);

void insert_case1(tree*& tr, tree* x) 
{
    if (x->parent == NULL) x->color = BLACK;
    else insert_case2(tr, x);
}

void insert_case2(tree*& tr, tree* x) 
{
    if (x->parent->color == RED) insert_case3(tr, x);
    else return;
}

void insert_case3(tree*& tr, tree* x) 
{
    tree* u = uncle(x);
    tree* g = grandparent(x);

    if (u != NULL && u->color == RED && x->parent->color == RED) 
    {
        x->parent->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        insert_case1(tr, g);
    }
    else 
    {
        insert_case4(tr, x);
    }
}

void insert_case4(tree*& tr, tree* x) 
{
    tree* g = grandparent(x);

    if (x == x->parent->right && x->parent == g->left) 
    {
        rotate_left(tr, x->parent);
        x = x->left;
    }
    else if (x == x->parent->left && x->parent == g->right) 
    {
        rotate_right(tr, x->parent);
        x = x->right;
    }
    insert_case5(tr, x);
}

void insert_case5(tree*& tr, tree* x) 
{
    tree* g = grandparent(x);
    x->parent->color = BLACK;
    g->color = RED;

    if (x == x->parent->left && x->parent == g->left) rotate_right(tr, g);
    else rotate_left(tr, g);
}

void insert(tree*& tr, tree* prev, int x) 
{
    if (x < prev->inf && prev->left == NULL) 
    {
        prev->left = node(prev, x);
        insert_case1(tr, prev->left);
    }
    else if (x > prev->inf && prev->right == NULL) 
    {
        prev->right = node(prev, x);
        insert_case1(tr, prev->right);
    }
    else if (x < prev->inf && prev->left != NULL) 
    {
        insert(tr, prev->left, x);
    }
    else if (x > prev->inf && prev->right != NULL) 
    {
        insert(tr, prev->right, x);
    }
}

void delete_case1(tree*& tr, tree* x);
void delete_case2(tree*& tr, tree* x);
void delete_case3(tree*& tr, tree* x);
void delete_case4(tree*& tr, tree* x);
void delete_case5(tree*& tr, tree* x);
void delete_case6(tree*& tr, tree* x);

void replace(tree*& tr, tree* x) 
{
    tree* ch = NULL;
    if (x->left != NULL) 
    {
        ch = x->left;
        ch->parent = x->parent;
        if (x->parent != NULL) 
        {
            if (x == x->parent->left) x->parent->left = ch;
            else x->parent->right = ch;
        }
        else tr = ch;
    }
    else if (x->right != NULL) 
    {
        ch = x->right;
        ch->parent = x->parent;
        if (x->parent != NULL) 
        {
            if (x == x->parent->left) x->parent->left = ch;
            else x->parent->right = ch;
        }
        else tr = ch;
    }
}

void delete_case1(tree*& tr, tree* x) 
{
    if (x->parent == NULL) 
    {
        if (x->left != NULL) tr = x->left;
        else tr = x->right;
    }
    else delete_case2(tr, x);
}

void delete_case2(tree*& tr, tree* x)
{
    tree* s = sibling(x);
    if (s != NULL && s->color == RED) 
    {
        x->parent->color = RED;
        s->color = BLACK;
        if (x == x->parent->left) rotate_left(tr, x->parent);
        else rotate_right(tr, x->parent);
    }
    delete_case3(tr, x);
}

void delete_case3(tree*& tr, tree* x) 
{
    tree* s = sibling(x);
    if (x->parent->color == BLACK && s != NULL && s->color == BLACK && (s->left == NULL || s->left->color == BLACK) && (s->right == NULL || s->right->color == BLACK)) 
    {
        s->color = RED;
        delete_case1(tr, x->parent);
    }
    else delete_case4(tr, x);
}

void delete_case4(tree*& tr, tree* x) 
{
    tree* s = sibling(x);
    if (x->parent->color == RED && s != NULL && s->color == BLACK && (s->left == NULL || s->left->color == BLACK) && (s->right == NULL || s->right->color == BLACK)) 
    {
        s->color = RED;
        x->parent->color = BLACK;
    }
    else delete_case5(tr, x);
}

void delete_case5(tree*& tr, tree* x) 
{
    tree* s = sibling(x);
    if (s->color == BLACK) 
    {
        if (x == x->parent->left && s->left != NULL && s->left->color == RED && (s->right == NULL || s->right->color == BLACK)) 
        {
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(tr, s);
        }
        else if (x == x->parent->right && s->right != NULL && s->right->color == RED && (s->left == NULL || s->left->color == BLACK)) 
        {
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(tr, s);
        }
    }
    delete_case6(tr, x);
}

void delete_case6(tree*& tr, tree* x) 
{
    tree* s = sibling(x);
    s->color = x->parent->color;
    x->parent->color = BLACK;
    if (x == x->parent->left) 
    {
        if (s->right != NULL) s->right->color = BLACK;
        rotate_left(tr, x->parent);
    }
    else 
    {
        if (s->left != NULL) s->left->color = BLACK;
        rotate_right(tr, x->parent);
    }
}

tree* find_node(tree* tr, int value) 
{
    while (tr != NULL && tr->inf != value) 
    {
        if (value < tr->inf) tr = tr->left;
        else tr = tr->right;
    }
    return tr;
}

void delete_one(tree*& tr, tree* x) 
{
    if (x->left != NULL && x->right != NULL) 
    {
        tree* buf = x->right;
        while (buf->left != NULL) buf = buf->left;
        x->inf = buf->inf;
        x = buf;
    }

    if (x->left != NULL || x->right != NULL) 
    {
        tree* ch = (x->left != NULL) ? x->left : x->right;
        replace(tr, x);
        if (x->color == BLACK) 
        {
            if (ch->color == RED) ch->color = BLACK;
            else delete_case1(tr, ch);
        }
    }
    else 
    {
        if (x->color == BLACK) delete_case1(tr, x);
        if (x->parent != NULL) 
        {
            if (x == x->parent->left) x->parent->left = NULL;
            else x->parent->right = NULL;
        }
    }
    delete x;
}

void delete_value(tree*& tr, int value) 
{
    tree* x = find_node(tr, value);
    if (x == NULL) 
    {
        std::cout << "Element " << value << " not found!" << std::endl;
        return;
    }
    delete_one(tr, x);
}

void inorder(tree* tr) 
{
    if (tr == NULL) return;
    inorder(tr->left);
    std::cout << tr->inf << " ";
    inorder(tr->right);
}

void sum_leaves(tree* tr, int& sum)
{
    if (tr == NULL) return;
    if (tr->left == NULL && tr->right == NULL) 
    {
        sum += tr->inf;
        return;
    }
    sum_leaves(tr->left, sum);
    sum_leaves(tr->right, sum);
}

void clear_tree(tree*& tr) 
{
    if (tr == NULL) return;
    clear_tree(tr->left);
    clear_tree(tr->right);
    delete tr;
    tr = NULL;
}


int main() 
{
    tree* tr = NULL;
    int n, temp;
    std::cout << "Enter N: "; std::cin >> n;

    std::cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> temp;
        if (i == 0) tr = root(temp);
        else 
        {
            insert(tr, tr, temp);
        }
    }

    std::cout << "\nInorder traversal: ";
    inorder(tr);

    int sum = 0;
    sum_leaves(tr, sum);
    std::cout << "\nSum of the leaves: " << sum;

    clear_tree(tr);
    return 0;
}
