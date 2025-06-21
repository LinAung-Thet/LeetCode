#include <iostream>
#include <vector>
#include <algorithm>

int minCoinsToAdd(std::vector<int>& coins, int target) {
    std::sort(coins.begin(), coins.end()); // ✅ Sort the coins
        int x = 1, addedCoins = 0, i = 0;

        while (x <= target) {
            if (i < coins.size() && coins[i] <= x) {
                x += coins[i]; // Expand reachable range
                i++;
            } else {
                x *= 2; // Add the smallest missing value
                addedCoins++;
            }
        }

        return addedCoins;
}

int main() {
    std::vector<int> coins = {1, 4, 10};
    int target = 19;

    int result = minCoinsToAdd(coins, target);
    std::cout << "Minimum coins to add: " << result << std::endl;

    return 0;
}