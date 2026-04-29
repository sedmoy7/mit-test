#include <iostream>
#include <vector>
#include <fstream>


struct queue
{
	int inf;
	queue* next;
};

void push(queue*& h, queue*& t, int x)
{
	queue* r = new queue;
	r->inf = x;
	r->next = NULL;
	if (!h && !t)
	{
		h = t = r;
	}
	else
	{
		t->next = r;
		t = r;
	}
}

int pop(queue*& h, queue*& t)
{
	queue* r = h;
	int i = h->inf;
	h = h->next;
	if (!h)
	{
		t = NULL;
	}
	delete r;
	return i;
}

void BFS(std::vector<std::vector<int>> Gr, int start, std::vector<int>& par, std::vector<int>& dist)
{
	queue* h = NULL;
	queue* t = NULL;
	int temp, y;

	dist[start] = 0;

	push(h, t, start);

	while (h && t)
	{
		temp = pop(h, t);

		for (int i = 0; i < Gr[temp].size(); i++)
		{
			if (dist[Gr[temp][i]] == -100)
			{
				y = Gr[temp][i];
				par[y] = temp;
				dist[y] = dist[temp] + 1;
				push(h, t, y);
			}
		}
	}
}

int main() {
	
	int N, m;
	std::vector<std::vector<int>> Gr;
	int u, v, A, B;
	/*
	std::cout << "Enter number of nodes: "; std::cin >> N;
	Gr.resize(N);

	std::cout << "Enter number of edges: "; std::cin >> m;

	std::cout << "Enter edges (u v):\n";
	for (int i = 0; i < m; i++) {
		std::cout << i + 1 << " edge: ";
		int u, v;
		std::cin >> u >> v;
		Gr[u].push_back(v);
		Gr[v].push_back(u);

	}
	*/

	std::ifstream fin("Task8_4.txt");
	fin >> N >> m;
	Gr.resize(N);
	for (int i = 0; i < m; i++) {
		fin >> u >> v;
		Gr[u].push_back(v);
		Gr[v].push_back(u);
	}

	std::cout << "\nGraph Adjacency List:\n";
	for (int i = 0; i < N; i++) {
		std::cout << i << ": ";
		for (int j = 0; j < Gr[i].size(); j++) {
			std::cout << Gr[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "\nEnter A and B: "; std::cin >> A >> B;

	std::vector<int> par(N, -1);
	std::vector<int> dist(N, -100);
	
	BFS(Gr, A, par, dist);

	if (dist[B] == -100)
	{
		std::cout << "\nA and B aren't connected!\n";
		return 1;
	}

	std::cout << "\nShortest path: ";
	std::vector<int> path;
	int curr = B;
	path.push_back(B);

	while (par[curr] != -1)
	{
		path.push_back(par[curr]);
		curr = par[curr];
	}

	for (int i = path.size() - 1; i >= 0; i--)
	{
		std::cout << path[i] << " ";
	}
	std::cout << "\nDistance between A and B = " << dist[B];
    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.