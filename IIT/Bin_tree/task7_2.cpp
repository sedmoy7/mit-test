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

void inorder(tree* tr)
{
	if (tr)
	{
		inorder(tr->left);
		if (tr->left && !tr->right) std::cout << tr->inf << " ";
		inorder(tr->right);
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

	std::cout << "\nResult: ";
	inorder(tr);

	return 0;
}

//5, 3, 7, 1, 9, 4, 2, 8, 6, 0


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.