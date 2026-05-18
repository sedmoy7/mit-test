#include <iostream>
#include <vector>
#include <algorithm>

std::vector<bool> used;
std::vector<int> order;
std::vector<std::vector<int>> gr;

void dfs(int x) 
{
    used[x] = true;
    for (int i = 0; i < gr[x].size(); i++) 
    {
        if (!used[gr[x][i]]) 
        {
            dfs(gr[x][i]);
        }
    }
    order.push_back(x);
}

int main() 
{
    int n, m;
    std::cout << "Enter number of nodes: "; std::cin >> n;
    std::cout << "Enter number of edges: "; std::cin >> m;
    gr.resize(n);

    std::cout << "Enter edges:\n";
    int x, y;
    for (int i = 0; i < m; i++) 
    {
        std::cin >> x >> y;
        gr[x].push_back(y);
    }

    used.assign(n, false);

    for (int i = 0; i < n; i++) 
    {
        if (!used[i]) 
        {
            dfs(i);
        }
    }
    reverse(order.begin(), order.end());
 
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) 
    {
        pos[order[i]] = i;
    }
    bool hasCycle = false;
    for (int i = 0; i < n; i++) 
    {
        for (int j=0; j<gr[i].size(); j++)
        {
            if (pos[i] > pos[gr[i][j]]) 
            {
                hasCycle = true;
                break;
            }
        }
        if (hasCycle) break;
    }

    if (hasCycle) 
    {
        std::cout << "\nGraph has a cycle! Topological sort is impossible!\n";
    }
    else 
    {
        std::cout << "\nTopological order: ";
        for (int i = 0; i < n; i++) 
        {
            std::cout << order[i] << " ";
        }
    }
    return 0;
}
