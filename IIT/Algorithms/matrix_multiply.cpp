//Coppersmith-Winograd matrix multiplication algorithm
#include <iostream>
#include <vector>

void print_matrix(std::vector<std::vector<int>> A) 
{
    for (int i = 0; i < A.size(); i++) 
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            std::cout << A[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

int main() {
    int M, N, N1, K;

    std::cout << "Enter the dimension of the matrix A: ";
    std::cin >> M >> N;
	
    std::vector<std::vector<int>> A(M, std::vector<int>(N));
    std::cout << "Enter the first matrix:\n";
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cin >> A[i][j];
        }
    }

    std::cout << "Enter the dimension of the matrix B: ";
    std::cin >> N1 >> K;

    if (N != N1)
    {
        std::cout << "\nError! The number of columns of the matrix A is NOT equal to the number of rows of the matrix B.\n";
        return 1;
    }

    std::vector<std::vector<int>> B(N, std::vector<int>(K));
    std::cout << "Enter the first matrix:\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < K; j++)
        {
            std::cin >> B[i][j];
        }
    }

    std::vector<std::vector<int>> C(M, std::vector<int>(K, 0));
    std::vector<int> row_factors(M, 0);
    std::vector<int> col_factors(K, 0);

    int d = N / 2;

    for (int i = 0; i < M; ++i) 
    {
        for (int j = 0; j < d; ++j) 
        {
            row_factors[i] += A[i][2 * j] * A[i][2 * j + 1];
        }
    }

    for (int i = 0; i < K; ++i) 
    {
        for (int j = 0; j < d; ++j) 
        {
            col_factors[i] += B[2 * j][i] * B[2 * j + 1][i];
        }
    }

    for (int i = 0; i < M; ++i) 
    {
        for (int j = 0; j < K; ++j) 
        {
            C[i][j] = -row_factors[i] - col_factors[j];
            for (int k = 0; k < d; ++k) 
            {
                C[i][j] += (A[i][2 * k] + B[2 * k + 1][j]) * (A[i][2 * k + 1] + B[2 * k][j]);
            }
        }
    }

    if (N % 2 != 0) 
    {
        for (int i = 0; i < M; ++i) 
        {
            for (int j = 0; j < K; ++j) 
            {
                C[i][j] += A[i][N - 1] * B[N - 1][j];
            }
        }
    }

    std::cout << "Matrix A (" << M << "x" << N << "):\n";
    print_matrix(A);

    std::cout << "\nMatrix B (" << N << "x" << K << "):\n";
    print_matrix(B);

    std::cout << "\nResult Matrix C (" << M << "x" << K << "):\n";
    print_matrix(C);

    return 0;
}
