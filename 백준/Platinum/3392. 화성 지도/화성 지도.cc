#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int n, x_1, y_1, x_2, y_2, newN = 32768, cnt[120000], tree[120000];
vector<pair<pii, pii>> v;

void update(int l, int r, int node, int s, int e, int diff) {
    if (s > r || e < l) return;
    
    if (s <= l && e >= r) cnt[node] += diff;
    else {
        int mid = (l + r) >> 1;
        update(l, mid, 2 * node, s, e, diff);
        update(mid + 1, r, 2 * node + 1, s , e, diff);
    }
    
    if (cnt[node] > 0) tree[node] = r - l + 1;
    else {
        if (l == r) tree[node] = 0;
        else tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    while (n--) {
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        v.push_back({{x_1, 1}, {y_1, y_2 - 1}});
        v.push_back({{x_2, -1}, {y_1, y_2 - 1}});
    }
    sort(v.begin(), v.end());
    int area = 0;
    int u = (*v.begin()).first.first;
    for (auto [x, y]: v) {
        area += (x.first - u) * tree[1];
        update(0, newN - 1, 1, y.first, y.second, x.second);
        u = x.first;
    }
    
    cout << area;
}