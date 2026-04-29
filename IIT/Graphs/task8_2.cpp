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
	
	std::cout << "\nEnter nodes that need to be erased (2 numbers from 0 to " << N-1 <<"): "; std::cin >> u >> v;

	if (v >= N || u>=N)
	{
		std::cout << "\nWrong number!\n";
		exit(0);
	}

	Gr[u].erase(remove(Gr[u].begin(), Gr[u].end(), v), Gr[u].end());
    Gr[v].erase(remove(Gr[v].begin(), Gr[v].end(), u), Gr[v].end());	

	std::cout << "\nResult Graph Adjacency List:\n";
	for (int i = 0; i < N; i++) {
		std::cout << i << ": ";
		for (int j = 0; j < Gr[i].size(); j++) {
			std::cout << Gr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
    return 0;
}