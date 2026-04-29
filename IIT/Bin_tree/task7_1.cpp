#include <iostream>
//#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//#include <windows.h>
//#include <iomanip>
//#include <string>
//#include <algorithm>
//#include <vector>
#include <cmath>
#include <queue>
//#include <math.h>
//#include <iomanip>
//#include <cctype>
//#include <iterator>
//#include <numeric>
//#include <functional>
//#include <fstream>
//#include <process.h>
//#include <typeinfo>
//#include "verylong.h"

//using namespace std;


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

int getHeight(tree* node)
{
	if (!node) return 0;
	return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

void print_Tree(tree* root)
{
	if (!root) return;

	int h = getHeight(root);

	std::queue<tree*> q;
	q.push(root);

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
			tree* current = nullptr;
			if (!q.empty())
			{
				current = q.front();
				q.pop();
			}

			if (current)
			{
				std::cout << current->inf;
				q.push(current->left);
				q.push(current->right);
			}
			else
			{
				std::cout << " ";
				q.push(nullptr);
				q.push(nullptr);
			}

			for (int j = 0; j < spaceBetween; j++)
				std::cout << " ";
		}

		std::cout << std::endl;
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

	std::cout << "\nEnter x: "; std::cin >> x;
	std::cout << "\nResult path: ";
	tree* tmp = tr;
	while (tmp->inf != x)
	{
		std::cout << tmp->inf << " ";
		if (x < tmp->inf)
		{
			tmp = tmp->left;
		}
		else
		{
			tmp = tmp->right;
		}
	}
	std::cout << x;
	return 0;
}

//5, 3, 7, 1, 9, 4, 2, 8, 6, 0