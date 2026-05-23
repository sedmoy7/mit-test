#include <iostream>

// Демонстрационная функция вычисления факториала
unsigned long long calculate_factorial(int n) 
{
    if (n == 0 || n == 1) 
    {
        return 1;
    } 
    else 
    {
        return n * calculate_factorial(n - 1);
    }
}

int main() 
{
    int test_value = 5;
    unsigned long long result = calculate_factorial(test_value);
    
    std::cout << "Factorial of " << testValue << " is equal " << result << std::endl;
    return 0;
}