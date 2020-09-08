#include <iostream>
#include <algorithm>
#include <vector>

void combinations_impl(int n, int k, int start, 
                       std::vector<int>& comb, 
                       std::vector<std::vector<int>>& combs)
{
    if (k == 0)
    {
        combs.push_back(comb);
        return;
    }
    
    for (int i = start; i < n; i++)
    {
        comb.push_back(i);
        combinations_impl(n, k - 1, i + 1, comb, combs);
        comb.pop_back();
    }
}

std::vector<std::vector<int>> combinations(int n, int k)
{
    std::vector<std::vector<int>> combs;
    std::vector<int> comb;
    combinations_impl(n, k, 0, comb, combs);
    
    return combs;
}

int main(int argc, char *argv[])
{
    int n, k;
    std::cin >> n >> k; 
    auto res = combinations(n, k);
    for (const auto& comb : res)
    {
        for (int a : comb)
            std::cout << a << " ";
        std::cout << "\n";    
    }
    return 0;
}
