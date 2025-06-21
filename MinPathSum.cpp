#include <iostream>
#include <vector>
#include <algorithm>

int minPathSum(std::vector<std::vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    // Traverse the grid starting from top-left
    for(int i=0; i<m; i++) {
        for( int j=0; j<n; j++) {
            if(i==0 && j==0) { continue; }
            else if(i==0) { grid[i][j] += grid[i][j-1]; }
            else if(j==0) { grid[i][j] += grid[i-1][j]; }
            else { grid[i][j] += std::min(grid[i-1][j], grid[i][j-1]); }
        }
    }
    return grid[m-1][n-1];
}

int main() {
    std::vector<std::vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    std::cout << "Minimum path sum: " << minPathSum(grid) << std::endl;
    return 0;
}