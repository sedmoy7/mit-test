#include <iostream>
#include <queue>
#include <string>

struct tree 
{ 
    char inf;
    tree* right;
    tree* left;
    tree* parent;
};

tree* node(char x) 
{ 
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

tree* create_tree(std::string str) 
{ 
    tree* tr = NULL;
    for (unsigned int i = 0; i < str.length(); i++) 
    { 
        tree* n = node(str[i]);
        if (str[i] == '-' || str[i] == '+') 
        {
            tr->parent = n;
            n->left = tr; 
            tr = n;
        }
        else if (str[i] == '/' || str[i] == '*') 
        {
            if (isdigit(tr->inf)) 
            {
                tr->parent = n;
                n->left = tr;
                tr = n;
            }
            else
            { 
                n->parent = tr;
                n->left = tr->right; 
                tr->right->parent = n;
                tr->right = n;
            }
        }
        else 
        { 
            if (!tr) tr = n; 
            else 
            { 
                if (!tr->right) 
                {
                    n->parent = tr;
                    n->left = tr->right;
                    tr->right = n;
                }
                else 
                {
                    tree* x = tr->right;
                    while (x->right) x = x->right;
                    n->parent = x->parent;
                    x->right = n;
                }
            }
        }
    }
    return tr;
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

void preorder(tree* tr) 
{
    if (tr) 
	{
        std::cout << tr->inf;
        preorder(tr->left);
        preorder(tr->right);
    }
}

void postorder(tree* tr) 
{
    if (tr) 
	{
        postorder(tr->left);
        postorder(tr->right);
        std::cout << tr->inf;
    }
}

int main() 
{
    std::string str;
    std::cout << "Enter expression: ";
    std::getline(std::cin, str);
    std::string znak = "+-/*0123456789";
    bool flag = true;
	
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (znak.find_first_of(str[i]) == std::string::npos)
        {
            flag = false;
            break;
        }
    }

    if (!flag) std::cout << "error";
    else 
    {
        tree* tr = create_tree(str);
        int n = str.length();
        int k = int(log((float)n) / log((float)2.0)) + 2;
        print(tr, k);
        std::cout << "\nPrefix form: "; preorder(tr);
        std::cout << "\nPostfix form: "; postorder(tr);
    }

    
    return 0;
}
