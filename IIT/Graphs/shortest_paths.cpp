#include <iostream>
#include <vector>

int main() 
{
    int n, m, start;
    std::cout << "Enter number of nodes: "; 
    std::cin >> n;
    std::cout << "Enter number of edges: "; 
    std::cin >> m;

    std::vector<std::vector<std::pair<int, int>>> gr(n);

    std::cout << "Enter edges and weight: ";
    int x, y, w;
    for (int i = 0; i < m; i++) 
    {
        std::cin >> x >> y >> w;
        gr[x].push_back({ y, w });
        gr[y].push_back({ x, w });
    }

    std::cout << "Enter start node: "; std::cin >> start;

    std::vector<int> dist(n, INT_MAX);   
    std::vector<int> parent(n, -1);      
    std::vector<bool> visited(n, false); 
    dist[start] = 0;

    for (int i = 0; i < n; i++) 
    {
        x = -1;
        int minDist = INT_MAX;

        for (int j = 0; j < n; j++) 
        {
            if (!visited[j] && dist[j] < minDist) 
            {
                minDist = dist[j];
                x = j;
            }
        }
        if (x == -1) break;
        visited[x] = true;

        for(int j = 0; j < gr[x].size(); j++)
        {
            y = gr[x][j].first;
            w = gr[x][j].second;

            if (!visited[y] && dist[x] + w < dist[y]) 
            {
                dist[y] = dist[x] + w;
                parent[y] = x;
            }
        }
    }

    for (int i = 0; i < n; i++) 
    {
        if (i == start) continue;
        std::cout << "\nNode " << i << ": ";
        if (dist[i] == INT_MAX) 
        {
            std::cout << "is not accessible\n";
            continue;
        }
        std::cout << "distance = " << dist[i] << std::endl;

        std::vector<int> path;
        int current = i;
        while (current != -1) 
        {
            path.push_back(current);
            current = parent[current];
        }

        std::cout << "Path: ";
        for (int j = path.size() - 1; j >= 0; j--) 
        {
            std::cout << path[j];
            if (j > 0) std::cout << " -> ";
        }
    }
    return 0;
}
