#include <iostream>
#include <vector>
#include <fstream>


void dfs(int v, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited)
{
	visited[v] = true;
	for (int u : adj[v]) {
		if (!visited[u]) {
			dfs(u, adj, visited);
		}
	}
}

int main() {
	
	int N, m;
	std::vector<std::vector<int>> Gr;
	int u, v;
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

	std::vector<bool> visited(N, false);

	dfs(0, Gr, visited);

	bool flag = true;
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			flag = false;
			break;
		}
	}

	if (flag)
	{
		std::cout << "\nGraph is connected.\n";
	}
	else
	{
		std::cout << "\nGraph is NOT connected.\n";
	}
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