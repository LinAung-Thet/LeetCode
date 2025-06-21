#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Function to compute the minimum number of coins needed
int minCoins(vector<int>& prices) {
    int n = prices.size();
    vector<int> dp(n + 1, INT_MAX); // dp[i]: min coins to get first i fruits
    dp[0] = 0; // No coins needed to take 0 fruits

    for (int i = 0; i < n; ++i) {
        // Option 1: buy the (i+1)th fruit
        // When buying the (i+1)th fruit, we can get the next i fruits for free
        for (int j = i + 1; j <= min(n, i + i + 2); ++j) {
            dp[j] = min(dp[j], dp[i] + prices[i]);
        }
    }

    return dp[n];
}

// Driver code
int main() {
    vector<vector<int>> testCases = {
        {3, 1, 2},
        {1, 10, 1, 1},
        {26, 18, 6, 12, 49, 7, 45, 45}
    };

    for (const auto& prices : testCases) {
        cout << "Input: ";
        for (int p : prices) cout << p << " ";
        cout << "\nOutput: " << minCoins(const_cast<vector<int>&>(prices)) << "\n\n";
    }
    int n;
    cin >> n; 
    string s = to_string(n);
    cout << "The input is " << s << endl;
    return 0;
}
