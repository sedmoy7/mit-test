#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
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


void replaceNode(tree*& tr, tree* old, tree* nw) {
	if (old->parent == NULL) {
		tr = nw;
	}
	else if (old == old->parent->left) {
		old->parent->left = nw;
	}
	else {
		old->parent->right = nw;
	}

	if (nw != NULL) {
		nw->parent = old->parent;
	}
}


tree* deleteNode(tree* tr, tree* z) {
	if (z->left == NULL) {
		replaceNode(tr, z, z->right);
	}
	else if (z->right == NULL) {
		replaceNode(tr, z, z->left);
	}
	else {
		tree* y = Min(z->right);
		if (y->parent != z) {
			replaceNode(tr, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		replaceNode(tr, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	delete z;
	return tr;
}

void removeOdds(tree*& tr, tree* curr) {
	if (curr == NULL) return;

	removeOdds(tr, curr->left);
	removeOdds(tr, curr->right);

	if (curr->inf % 2 != 0) {
		tr = deleteNode(tr, curr);
	}
}

const int N = 10;

int main()
{
	tree* tr = NULL;
	int temp, x;
	std::cout << "Enter N elements: ";
	for (int i = 0; i < N; i++)
	{
		//temp = i + 1;
		std::cin >> temp;
		insert(tr, temp);
	}

	print_Tree(tr);

	removeOdds(tr, tr);

	std::cout << "\nResult:\n";
	print_Tree(tr);

	return 0;
}

//5, 3, 7, 1, 9, 4, 2, 8, 6, 0

