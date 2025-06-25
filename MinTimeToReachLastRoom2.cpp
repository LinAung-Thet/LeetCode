#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

// https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/?envType=problem-list-v2&envId=shortest-path

class State {
public:
    int x;
    int y;
    int dis;
    State(int x, int y, int dis) : x(x), y(y), dis(dis) {}
};

int getTransitTime(int x, int y) {
    if(x == 0 && y == 0) return 0;
    int mod = ((x+y)%2) == 1 ? 1 : 2 ;
    return mod;
}

int minTimeToReachEnd(vector<vector<int>>& moveTime) {
    // int inf = 0x3f3f3f3f;
    // int n = moveTime.size(), m = moveTime[0].size();
    // vector<vector<int>> d(n, vector<int>(m, inf));
    // vector<vector<int>> v(n, vector<int>(m, 0));

    // int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    // d[0][0] = 0;

    // auto cmp = [](const State& a, const State& b) { return a.dis > b.dis; };

    // priority_queue<State, vector<State>, decltype(cmp)> q(cmp);
    // q.push(State(0, 0, 0));

    // while (!q.empty()) {
    //     State s = q.top();
    //     q.pop();
    //     if (v[s.x][s.y]) continue;
    //     v[s.x][s.y] = 1;

    //     for (int i = 0; i < 4; i++) {
    //         int nx = s.x + dirs[i][0];
    //         int ny = s.y + dirs[i][1];
    //         if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

    //         int dist = max(d[s.x][s.y], moveTime[nx][ny]) + 1;
    //         if (d[nx][ny] > dist) {
    //             d[nx][ny] = dist;
    //             q.push(State(nx, ny, dist));
    //         }
    //     }
    // }

    // return d[n - 1][m - 1];

    int n = moveTime.size();
    int m = moveTime[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));

    auto cmp = [](State& a, State& b) {return (a.dis > b.dis);};
    priority_queue<State, vector<State>, decltype(cmp)> pq(cmp);

    vector<pair<int, int>> dirs = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    distance[0][0] = 0;
    
    pq.push(State(0, 0, 0));

    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (visited[s.x][s.y]) continue;
        visited[s.x][s.y] = true;

        for(auto [dx, dy] : dirs) {
            int nextX = s.x + dx;
            int nextY = s.y + dy;
            if (nextX < 0 || nextX >= n || nextY < 0 || nextY >= m) continue;

            int newDist = max(distance[s.x][s.y], moveTime[nextX][nextY]) + getTransitTime(nextX, nextY);
            if (newDist < distance[nextX][nextY]) {
                distance[nextX][nextY] = newDist;
                pq.push(State(nextX, nextY, newDist));
            }
        }
    }
    return distance[n-1][m-1];
}

int main() {
    vector<vector<int>> test1 = {{0,4},{4,4}};
    cout << "Test 1 Output: " << minTimeToReachEnd(test1) << " (Expected: 7)" << endl;

    vector<vector<int>> test2 = {{0,0,0,0},{0,0,0,0}};
    cout << "Test 2 Output: " << minTimeToReachEnd(test2) << " (Expected: 6)" << endl;

    vector<vector<int>> test3 = {{0,1},{1,2}};
    cout << "Test 3 Output: " << minTimeToReachEnd(test3) << " (Expected: 4)" << endl;

    vector<vector<int>> test4 = {{17,56},{97,80}};
    cout << "Test 4 Output: " << minTimeToReachEnd(test4) << " (Expected: 81)" << endl;

    return 0;
}
