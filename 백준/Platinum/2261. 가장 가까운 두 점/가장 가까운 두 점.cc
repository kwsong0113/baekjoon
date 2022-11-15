#include <bits/stdc++.h>
using namespace std;
int n, x, y;
vector<pair<int, int>> points;
const int INF = 1e9;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second < b.second;
}

int dist(int a, int b) {
    int dx = points[a].first - points[b].first, dy = points[a].second - points[b].second;
    return dx * dx + dy * dy;
}

int minDist(int l, int r) {
    if (l == r) return INF;
    if (r == l + 1) return dist(l, r);
    
    int mid = (l + r) >> 1;
    int minD = INF;
    minD = min(minD, minDist(l, mid));
    minD = min(minD, minDist(mid + 1, r));
    
    int midX = points[mid].first;
    vector<pair<int, int>> between;
    
    for (int i = l; i <= r; ++i) {
        int x = points[i].first;
        if ((midX - x) * (midX - x) <= minD) between.push_back(points[i]);
    }
    sort(between.begin(), between.end(), cmp);
    
    for (int i = 0; i < between.size(); ++i) {
        for (int j = i + 1; j < between.size(); ++j) {
            int dx = between[j].first - between[i].first, dy = between[j].second - between[i].second;
            if (dy * dy >= minD) break;
            minD = min(minD, dx * dx + dy * dy);
        }
    }
    return minD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end());
    cout << minDist(0, n - 1);
}