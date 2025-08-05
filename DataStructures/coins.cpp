#include <iostream>
#include <vector>
using namespace std;

int greedyCoinChange(int amount, const vector<int> &coins)
{
    int coinCount = 0;
    for (int i = coins.size() - 1; i >= 0; i--)
    {
        while (amount >= coins[i])
        {
            amount -= coins[i];
            coinCount++;
        }
    }
    return coinCount;
}

int main()
{
    vector<int> coins = {1, 5, 10, 25}; // Denominations
    int amount = 63;                    // Amount we need to make
    cout << "Minimum coins needed: " << greedyCoinChange(amount, coins) << endl;
    return 0;
}
