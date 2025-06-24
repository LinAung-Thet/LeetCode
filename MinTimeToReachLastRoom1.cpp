#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

// https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/?envType=problem-list-v2&envId=shortest-path

int minTimeToReachEnd(vector<vector<int>>& moveTime) {
    int n = moveTime.size(), m = moveTime[0].size();
    vector<vector<int>> minTime(n, vector<int>(m, INT_MAX));
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    minTime[0][0] = 0;
    pq.emplace(0, 0, 0); // (time, x, y)

    vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};

    while (!pq.empty()) {
        auto [time, x, y] = pq.top(); pq.pop();
        if (x == n - 1 && y == m - 1) return time;

        if (time > minTime[x][y]) continue;

        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            int arrivalTime = time + 1;
            int openTime = moveTime[nx][ny];

            // // If arrival time is less than the room's open time, we may need to wait.
            // if (arrivalTime < openTime) {
            //     int waitTime = openTime - arrivalTime;
            //     // Wait until we land on a time of the correct parity for movement
            //     if (waitTime % 2 == 1) waitTime++;
            //     arrivalTime += waitTime;
            // }

            if (x != n - 1 && y != m - 1)
                arrivalTime += openTime;

            if (arrivalTime < minTime[nx][ny]) {
                minTime[nx][ny] = arrivalTime;
                pq.emplace(arrivalTime, nx, ny);
            }
        }
    }

    return -1;
}

int main() {
    vector<vector<int>> test1 = {{0,4},{4,4}};
    cout << "Test 1 Output: " << minTimeToReachEnd(test1) << " (Expected: 6)" << endl;

    vector<vector<int>> test2 = {{0,0,0},{0,0,0}};
    cout << "Test 2 Output: " << minTimeToReachEnd(test2) << " (Expected: 3)" << endl;

    vector<vector<int>> test3 = {{0,1},{1,2}};
    cout << "Test 3 Output: " << minTimeToReachEnd(test3) << " (Expected: 3)" << endl;

    return 0;
}
