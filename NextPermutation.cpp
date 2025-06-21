#include <iostream>
#include <vector>
#include <algorithm>

void nextPermutation(std::vector<int>& nums) {
    int n = nums.size(), i = n - 2;

    // Find the first decreasing element from the right
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }

    if (i >= 0) {
        // Find the next larger element to swap with nums[i]
        int j = n - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        std::swap(nums[i], nums[j]);
    }

    // Reverse the elements after index i
    std::reverse(nums.begin() + i + 1, nums.end());
}

int main() {
    std::vector<int> nums = {3, 1, 4, 2 };
    
    nextPermutation(nums);

    std::cout << "Next permutation: ";
    for (int num : nums) {
        std::cout << num << " ";
    }

    return 0;
}