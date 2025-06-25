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

int minTimeToReachEnd(vector<vector<int>>& moveTime) {
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

            int newDist = max(distance[s.x][s.y], moveTime[nextX][nextY]) + (s.x + s.y) % 2 + 1;
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
    cout << "Test 4 Output: " << minTimeToReachEnd(test4) << " (Expected: 82)" << endl;

    return 0;
}
