#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<pair<int, int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};

// Compute distance from each cell to nearest thief using BFS
vector<vector<int>> computeSafeness(const vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    queue<pair<int, int>> q;

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            if (grid[r][c] == 1) {
                dist[r][c] = 0;
                q.push({r, c});
            }

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nc >= 0 && nr < n && nc < n && dist[nr][nc] > dist[r][c] + 1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return dist;
}

// Try greedy traversal from (0,0) to (n-1,n-1)
bool greedySafestPath(const vector<vector<int>>& dist, vector<pair<int, int>>& path) {
    int n = dist.size();
    int r = 0, c = 0;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    visited[r][c] = true;
    path.push_back({r, c});

    while (r != n - 1 || c != n - 1) {
        int bestScore = -1;
        pair<int, int> next = {-1, -1};
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nc >= 0 && nr < n && nc < n && !visited[nr][nc]) {
                if (dist[nr][nc] > bestScore) {
                    bestScore = dist[nr][nc];
                    next = {nr, nc};
                }
            }
        }

        if (next.first == -1) return false; // No unvisited neighbor found

        r = next.first; c = next.second;
        visited[r][c] = true;
        path.push_back(next);
    }

    return true;
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    auto dist = computeSafeness(grid);
    vector<pair<int, int>> path;

    if (greedySafestPath(dist, path)) {
        cout << "Greedy path found with all local max safeness steps:\n";
        for (auto [r, c] : path)
            cout << "(" << r << "," << c << ") -> ";
        cout << "END\n";
    } else {
        cout << "Greedy path could not reach the destination.\n";
    }

    return 0;
}