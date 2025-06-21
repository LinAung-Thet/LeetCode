#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minJumps(vector<int>& nums) {
    int n = nums.size();
    int jumps = 0;
    int farthest = 0;
    int end = 0;

    // We do not need to jump from the last index
    for (int i = 0; i < n - 1; ++i) {
        farthest = max(farthest, i + nums[i]);

        // If we reach the end of the current jump range
        if (i == end) {
            ++jumps;
            end = farthest;
        }
    }

    return jumps;
}

// Driver code
int main() {
    vector<vector<int>> testCases = {
        {2, 3, 1, 1, 4},
        {2, 3, 0, 1, 4},
        {1, 2, 3},
        {1, 1, 1, 1},
        {5, 4, 3, 2, 1, 0, 1}
    };

    for (const auto& nums : testCases) {
        cout << "Input: ";
        for (int num : nums) cout << num << " ";
        cout << "\nOutput: " << minJumps(const_cast<vector<int>&>(nums)) << "\n\n";
    }

    return 0;
}
