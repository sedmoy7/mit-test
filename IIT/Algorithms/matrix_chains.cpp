#include <iostream>
#include <vector>
#include <string>

struct optimization_result 
{
    std::vector<std::vector<int>> m; 
    std::vector<std::vector<int>> s; 
};

optimization_result matrix_chain_order(std::vector<int>& p) 
{
    int n = p.size() - 1;

    std::vector<std::vector<int>> m(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> s(n + 1, std::vector<int>(n + 1, 0));

    for (int l = 2; l <= n; ++l) 
    {
        for (int i = 1; i <= n - l + 1; ++i) 
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; ++k) 
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k; 
                }
            }
        }
    }
    return { m, s };
}

std::string get_optimal_parens(std::vector<std::vector<int>>& s, int i, int j) 
{
    if (i == j) 
	{
        return "A" + std::to_string(i);
    }
    else 
	{
        std::string left = get_optimal_parens(s, i, s[i][j]);
        std::string right = get_optimal_parens(s, s[i][j] + 1, j);
        return "(" + left + " x " + right + ")";
    }
}

int main() 
{
    int n;
    std::cout << "Enter number of matrixes to multiply: ";
    std::cin >> n;

    std::vector<int> matrix_sizes(n + 1);

    std::cout << "Enter number of rows for the matrix A1: ";
    std::cin >> matrix_sizes[0];

    for (int i = 1; i <= n; ++i) 
    {
        std::cout << "Enter number of columns for matrix A" << i << " (dimesionality: " << matrix_sizes[i - 1] << " x ?): ";
        std::cin >> matrix_sizes[i];
    }

    optimization_result result = matrix_chain_order(matrix_sizes);

    std::cout << "\nResult:\n";
    std::cout << "Minimum number of scalar multiplications: " << result.m[1][n] << "\n";
    std::cout << "Optimal multiplication order: " << get_optimal_parens(result.s, 1, n) << "\n";

    return 0;
}
