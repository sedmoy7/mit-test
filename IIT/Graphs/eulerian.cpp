#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


int main() 
{
    int n, m;
    std::cout << "Enter number of nodes: "; std::cin >> n;
    std::cout << "Enter number of edges: "; std::cin >> m;
    std::vector<std::vector<int>> gr(n);
    std::vector<int> step(n, 0);

    std::cout << "Enter edges: \n";
    int x, y;
    for (int i = 0; i < m; i++) 
    {
        std::cin >> x >> y;
        gr[x].push_back(y);
        gr[y].push_back(x);
        step[x]++;
        step[y]++;
    }

    int v1 = -1, v2 = -1;
    for (int i = 0; i < n; i++) 
    {
        if (step[i] % 2 == 1) 
        {
            if (v1 == -1) v1 = i;
            else if (v2 == -1) v2 = i;
            else 
            {
                std::cout << "\nThere is not Eulerian cycle or path!\n";
                return 0;
            }
        }
    }

    bool hasFakeEdge = (v1 != -1);
    if (hasFakeEdge) 
    {
        gr[v1].push_back(v2);
        gr[v2].push_back(v1);
        step[v1]++;
        step[v2]++;
    }

    std::stack<int> st;
    std::vector<int> result;

    int start = 0;
    if (v1 != -1) start = v1;
    st.push(start);

    while (!st.empty())
    {
        int cur = st.top();

        if (!gr[cur].empty()) 
        {
            int neighbor = gr[cur][0];

            auto it1 = std::find(gr[cur].begin(), gr[cur].end(), neighbor);
            if (it1 != gr[cur].end()) gr[cur].erase(it1);

            auto it2 = std::find(gr[neighbor].begin(), gr[neighbor].end(), cur);
            if (it2 != gr[neighbor].end()) gr[neighbor].erase(it2);

            st.push(neighbor);
        }
        else 
        {
            result.push_back(cur);
            st.pop();
        }
    }

    if (hasFakeEdge) 
    {
        for (size_t i = 0; i + 1 < result.size(); i++) 
        {
            if ((result[i] == v1 && result[i + 1] == v2) || (result[i] == v2 && result[i + 1] == v1)) 
            {
                std::vector<int> new_result;
                for (size_t j = i + 1; j < result.size(); j++)
                    new_result.push_back(result[j]);
                for (size_t j = 0; j <= i; j++)
                    new_result.push_back(result[j]);
                result = new_result;
                break;
            }
        }
        result.pop_back();
    }
    
    bool hasEdges = false;
    for (int i = 0; i < n; i++) 
    {
        if (!gr[i].empty()) 
        {
            hasEdges = true;
            break;
        }
    }

    if (hasEdges) 
    {
        std::cout << "\nGraph is not connected, there is no Eulerian cycle! \n";
    }
    else 
    {
        std::cout << "\nEulerian ";
        if (v1 == -1) std::cout << "cycle: ";
        else std::cout << "path: ";

        for (int i = result.size() - 1; i >= 0; i--) 
        {
            std::cout << result[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << std::endl;
    }

    return 0;
}
