#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int n, x, y, w, h, link[50001], s[50001], area[50001];
pii state[100000];
unordered_map<int, int> yComp;
vector<pair<pii, pii>> points;
vector<int> yCoords;

int find(int x) {
    if (link[x] == x) return x;
    return link[x] = find(link[x]);
}

bool same(int a, int b) {
    return find(a) == find(b);
}

void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (s[a] < s[b]) swap(a, b);
    s[a] += s[b];
    area[a] += area[b];
    link[b] = a;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x >> y >> w >> h;
        points.push_back({{x, -i}, {y, y + h}});
        points.push_back({{x + w, i}, {y, y + h}});
        yCoords.push_back(y);
        yCoords.push_back(y + h);
        link[i] = i; s[i] = 1; area[i] = w * h;
    }
    
    sort(yCoords.begin(), yCoords.end());
    int idx = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (i > 0 && yCoords[i] != yCoords[i - 1]) idx++;
        yComp[yCoords[i]] = idx;
    }
    for (int i = 0; i < 2 * n; ++i) {
        auto [y_1, y_2] = points[i].second;
        points[i].second = {yComp[y_1], yComp[y_2]};
    }
    
    sort(points.begin(), points.end());
    
    for (auto [u, v]: points) {
        auto [y_1, y_2] = v;
        if (u.second < 0) {
            for (int y = y_1; y <= y_2; ++y) {
                if (state[y].second == 0) state[y] = {-u.second, 1};
                else {
                    unite(-u.second, state[y].first);
                    state[y].second++;
                }
            }
        } else {
            for (int y = y_1; y <= y_2; ++y) {
                state[y].second--;
            }
        }
    }
    
    int maxArea = 0;
    for (int i = 1; i <= n; ++i) {
        maxArea = max(maxArea, area[i]);
    }
    cout << maxArea;
    
}