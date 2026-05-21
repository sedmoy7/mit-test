#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int power(int x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;  

    while (y > 0)
    {
        if (y % 2 == 1)
        {
            res = (res * x) % p;
        }
        y = y / 2;
        x = (x * x) % p;
    }
    return res;
}

bool miiller_test(int d, int n)
{
    srand(time(0));
    int a = 2 + rand() % (n - 4);

    int x = power(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1)
    {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)      return false;
        if (x == n - 1)    return true;
    }

    return false;
}

bool is_prime(int n, int k)
{
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;

    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++)
    {
        if (!miiller_test(d, n))
            return false;
    }
        
    return true;
}

const int k = 4;

int main()
{
    int n;
    std::cout << "Enter a number: ";
    std::cin >> n;
    if (is_prime(n, k))
    {
        std::cout << "\nNumber " << n << " is prime\n";
    }
    else
    {
        std::cout << "\nNumber " << n << " is composite\n";
    }

    return 0;
}
