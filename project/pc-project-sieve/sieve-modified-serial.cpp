#include <bits/stdc++.h>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

int eratosthenes(int lastNumber)
{
    int memorySize = (lastNumber - 1) / 2;
    char *isPrime = new char[memorySize + 1];
    for (int i = 0; i <= memorySize; i++)
        isPrime[i] = 1;
    for (int i = 3; i * i <= lastNumber; i += 2)
        if (isPrime[i / 2])
            for (int j = i * i; j <= lastNumber; j += 2 * i)
                isPrime[j / 2] = 0;
    int found = lastNumber >= 2 ? 1 : 0;
    for (int i = 1; i <= memorySize; i++)
        found += isPrime[i];
    delete[] isPrime;
    return found;
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    if (argc > 1)
    {
        try
        {
            n = stoi(argv[1]);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
        clock_t begin = clock();
    int x=eratosthenes(n);
        clock_t end = clock();
    cout << x << " prime numbers in\n";
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
    cout << "The running time is " << time_spent << " milliseconds." << endl;
        return 0;
}
// g++ -std=c++11 basic.cpp && ./a.out