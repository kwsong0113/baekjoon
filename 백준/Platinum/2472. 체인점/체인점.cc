#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

int n, m, x, y, z, t, q, apart[3], dist[3][100001], tree[400000], N;
vector<pii> adj[100001];
vector<pair<tuple<int, int, int>, int>> v;
const int INF = 2e9;

void dijkstra(int u) {
    priority_queue<pii> pq;
    bool processed[n + 1] = {false};
    for (int i = 1; i <= n; ++i) dist[u][i] = INF;
    dist[u][apart[u]] = 0;
    pq.push({0, apart[u]});
    while (!pq.empty()) {
        int x = pq.top().second; pq.pop();
        if (processed[x]) continue;
        processed[x] = true;
        for (auto [y, z]: adj[x]) {
            if (dist[u][y] > dist[u][x] + z) {
                dist[u][y] = dist[u][x] + z;
                pq.push({-dist[u][y], y});
            }
        }
    }
}

bool cmp1(pair<tuple<int, int, int>, int> u, pair<tuple<int, int, int>, int> v) {
    return get<1>(u.first) < get<1>(v.first);
}

// bool cmp2(pair<tuple<int, int, int>, int> u, pair<tuple<int, int, int>, int> v) {
//     int a1, b1, c1, a2, b2, c2;
//     tie(a1, b1, c1) = u.first; tie(a2, b2, c2) = v.first;
//     if (a1 == a2) {
//         if (b1 == b2) return c1 > c2;
//         return b1 > b2;
//     }
//     return a1 > a2;
// }

void update(int node, int s, int e, int index, int val) {
    if (index > e || index < s) return;
    tree[node] = min(tree[node], val);
    if (s != e) {
        int mid = (s + e) / 2;
        update(2 * node, s, mid, index, val);
        update(2 * node + 1, mid + 1, e, index, val);
    }
}

int minVal(int node, int s, int e, int l, int r) {
    if (l > e || r < s) return INF;
    if (s >= l && e <= r) return tree[node];
    int mid = (s + e) / 2;
    return min(minVal(2 * node, s, mid, l, r), minVal(2 * node + 1, mid + 1, e, l, r));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    cin >> apart[0] >> apart[1] >> apart[2];
    cin >> m;
    while (m--) {
        cin >> x >> y >> z;
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
    }
    for (int u = 0; u < 3; ++u) dijkstra(u);
    
    for (int i = 1; i <= n; ++i) v.push_back({{dist[0][i], dist[1][i], dist[2][i]}, i});
    sort(v.begin(), v.end(), cmp1);
    int cnt = 0;
    int da, db, dc;
    for (int i = 0; i < n; ++i) {
        tie(da, db, dc) = v[i].first;
        v[i].first = {da, cnt, dc};
        if (i < n - 1 && db != get<1>(v[i + 1].first)) cnt++;
    }
    
    N = 1 << ((int)ceil(log2(cnt + 1)));
    sort(v.begin(), v.end());
    
    int currDA = get<0>(v[0].first);
    queue<pii> updateQ;
    bool ans[n + 1];
    memset(ans, true, sizeof(ans));
    for (int i = 0; i < 2 * N; ++i) tree[i] = INF;
    for (int i = 0; i < n; ++i) {
        tie(da, db, dc) = v[i].first;
        if (da != currDA) {
            while (!updateQ.empty()){
                auto [db1, dc1] = updateQ.front(); updateQ.pop();
                if (dc1 >= tree[N + db1]) continue;
                update(1, 0, N - 1, db1, dc1);
            }
        }
        if (minVal(1, 0, N - 1, 0, db - 1) < dc) ans[v[i].second] = false;
        updateQ.push({db, dc});
        
        currDA = da;
    }
    
    cin >> t; 
    while (t--) {
        cin >> q;
        cout << (ans[q] ? "YES" : "NO") << "\n";
    }
}