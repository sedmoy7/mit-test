#include <iostream>
#include <vector>
#include <fstream>


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

	std::ifstream fin("Task8_1.txt");
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

	std::cout << "\nResult List:\n";
	for (int i = 0; i < N; i++) {
		std::cout << i << ": " << Gr[i].size() << std::endl;;
	}
    return 0;
}