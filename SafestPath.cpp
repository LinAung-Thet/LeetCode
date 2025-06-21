#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int maximumSafenessFactor(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    // Multi-source BFS: compute distance from each cell to nearest thief
    queue<pair<int, int>> q;
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            if (grid[r][c] == 1) {
                dist[r][c] = 0;
                q.push({r, c});
            }

    vector<pair<int, int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] > dist[r][c] + 1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    // Max-heap BFS (Dijkstra-like): maximize minimum safeness factor along the path
    priority_queue<tuple<int, int, int>> pq;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    pq.push({dist[0][0], 0, 0});  // {safeness, row, col}

    while (!pq.empty()) {
        auto [safe, r, c] = pq.top(); pq.pop();
        if (r == n - 1 && c == n - 1) 
        return safe;
        if (visited[r][c]) continue;
        visited[r][c] = true;

        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                int newSafe = min(safe, dist[nr][nc]);
                pq.push({newSafe, nr, nc});
            }
        }
    }

    return -1; // Should not reach here
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 1},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    };

    int result = maximumSafenessFactor(grid);
    cout << "Maximum safeness factor: " << result << endl;
    return 0;
}
