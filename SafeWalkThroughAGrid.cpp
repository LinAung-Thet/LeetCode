#include <iostream>
#include <vector>
#include <queue>

struct State {
    int row, col, health;
};

bool canReachWithHealth(std::vector<std::vector<int>>& grid, int health) {
    int m = grid.size(), n = grid[0].size();
    std::vector<std::vector<int>> maxHealth(m, std::vector<int>(n, -1));

    std::queue<State> q;
    q.push({0, 0, health - grid[0][0]});
    maxHealth[0][0] = health - grid[0][0];

    std::vector<std::pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (cur.health < 1) continue;

        for (auto [dx, dy] : directions) {
            int newRow = cur.row + dx;
            int newCol = cur.col + dy;

            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n) {
                int newHealth = cur.health - grid[newRow][newCol];
                if (newHealth > maxHealth[newRow][newCol]) {
                    maxHealth[newRow][newCol] = newHealth;
                    q.push({newRow, newCol, newHealth});
                }
            }
        }
    }

    return maxHealth[m - 1][n - 1] >= 1;
}

int main() {
    std::vector<std::vector<int>> grid = {
        {0, 1, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    int health = 1;

    std::cout << (canReachWithHealth(grid, health) ? "Reachable" : "Not reachable") << std::endl;
    return 0;
}