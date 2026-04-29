#include <iostream>
#include <vector>
#include <queue>

struct tree
{
	int inf;
	tree* right;
	tree* left;
	tree* parent;
};

tree* node(int x)
{
	tree* n = new tree;
	n->inf = x;
	n->left = n->right = NULL;
	n->parent = NULL;
	return n;
}

void insert(tree*& tr, int x)
{
	tree* n = node(x);
	if (!tr)
		tr = n;
	else
	{
		tree* y = tr;
		while (y)
		{
			if ((n->inf) > (y->inf))
			{
				if ((y->right))
				{
					y = y->right;
				}
				else
				{
					n->parent = y;
					y->right = n;
					break;
				}
			}
			else if (n->inf < y->inf)
			{
				if (y->left)
				{
					y = y->left;
				}
				else
				{
					n->parent = y;
					y->left = n;
					break;
				}
			}
		}
	}
}


tree* find(tree* tr, int x)
{
	if (!tr || x == tr->inf)
	{
		return tr;
	}
	if (x < tr->inf)
	{
		return find(tr->left, x);
	}
	else
	{
		return find(tr->right, x);
	}
}

tree* Max(tree* tr)
{
	if (!tr->right) return tr;
	else return Max(tr->right);
}


tree* Min(tree* tr)
{
	if (!tr->left) return tr;
	else return Min(tr->left);
}

tree* Next(tree* tr, int x)
{
	tree* n = find(tr, x);
	if (n->right)
	{
		return Min(n->right);
	}
	tree* y = n->parent;
	while (y && n == y->right)
	{
		n = y;
		y = y->parent;
	}
	return y;
}


int getHeight(tree* node)
{
	if (!node) return 0;
	return 1 + std::max(getHeight(node->left), getHeight(node->right));
}


void print_Tree(tree* tr)
{
	if (!tr) return;

	int h = getHeight(tr);

	std::queue<tree*> q;
	q.push(tr);

	const int MAX_SPACES = 10;    

	for (int level = 0; level < h; level++)
	{
		int levelNodes = 1 << level;

		int spaceBetween = ((1 << (h - level)) - 1);
		int leadingSpaces = ((1 << (h - level - 1)) - 1);

		spaceBetween = std::min(spaceBetween, MAX_SPACES);
		leadingSpaces = std::min(leadingSpaces, MAX_SPACES);

		for (int i = 0; i < leadingSpaces; i++)
			std::cout << " ";

		for (int i = 0; i < levelNodes; i++)
		{
			tree* curr = NULL;
			if (!q.empty())
			{
				curr = q.front();
				q.pop();
			}

			if (curr)
			{
				std::cout << curr->inf;
				q.push(curr->left);
				q.push(curr->right);
			}
			else
			{
				std::cout << " ";
				q.push(NULL);
				q.push(NULL);
			}

			for (int j = 0; j < spaceBetween; j++)
				std::cout << " ";
		}

		std::cout << std::endl;
	}
}


void Delete(tree*& tr, tree* v)
{
	tree* p = v->parent;
	if (p == NULL)
	{
		tree* succ = Max(tr->left);
		v->inf = succ->inf;
		if (succ->parent->left == succ)
		{
			succ->parent->left = succ->right;
			if (succ->right)
				succ->right->parent = succ->parent;
		}
		else
		{
			succ->parent->right = succ->right;
			if (succ->right)
				succ->right->parent = succ->parent;
		}
		delete succ;
	}
		
	else if (!v->left && !v->right)
	{
		if (p->left == v)
		{
			p->left = NULL;
		}
		if (p->right == v)
		{
			p->right = NULL;
		}
		delete v;
	}
	else if (!v->left || !v->right)
	{
		if (p == NULL)
		{
			if (!v->left)
			{
				tr = v->right;
				v->parent = NULL;
			}
			else
			{
				tr = v->left;
				v->parent = NULL;
			}
		}
		else
		{
			if (!v->left)
			{
				if (p->left == v)
				{
					p->left = v->right;
				}
				else
				{
					p->right = v->right;
				}
				v->right->parent = p;
			}
			else
			{
				if (p->left == v)
				{
					p->left = v->left;
				}
				else
				{
					p->right = v->left;
				}
				v->left->parent = p;
			}
			delete v;
		}
	}
	else
	{
		tree* succ = Next(tr, v->inf);
		v->inf = succ->inf;
		if (succ->parent->left == succ)
		{
			succ->parent->left = succ->right;
			if (succ->right)
				succ->right->parent = succ->parent;
		}
		else
		{
			succ->parent->right = succ->right;
			if (succ->right)
				succ->right->parent = succ->parent;
		}
		delete succ;
	}
}

/*
void removeOdds(tree*& tr, tree* curr) {
	if (curr == NULL) return;
	tree* leftch = curr->left;
	tree* rightch = curr->right;
	if (curr->inf % 2 != 0) {
		Delete(tr, curr);
	}
	removeOdds(tr, leftch);
	removeOdds(tr, rightch);
}
*/

//5, 3, 7, 1, 9, 4, 2, 8, 6, 0
int main()
{
	tree* tr = NULL;
	int temp, x, N;
	std::vector<int> vec;
	std::cout << "Enter N: "; std::cin >> N;
	std::cout << "Enter elements: ";
	for (int i = 0; i < N; i++)
	{
		//temp = i + 1;
		std::cin >> temp;
		if (temp % 2 == 1)
		{
			vec.push_back(temp);
		}
		insert(tr, temp);
	}

	print_Tree(tr);

	//removeOdds(tr, tr);

	for (auto iter = vec.begin(); iter != vec.end(); iter++)
	{
		Delete(tr, find(tr, (*iter)));
		//std::cout << "\nDeleted: "<< (*iter) << std::endl;
		//print_Tree(tr);
	}
	std::cout << "\nResult:\n";
	print_Tree(tr);

	return 0;
}