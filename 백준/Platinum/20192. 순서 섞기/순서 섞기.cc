#include <bits/stdc++.h>
using namespace std;
int n, prev_a, a;
vector<int> v;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        if (i > 0) {
            if (a == prev_a) continue;
            else if (a > prev_a && (v.empty() || v.back() == -1)) v.push_back(1);
            else if (a < prev_a && (v.empty() || v.back() == 1)) v.push_back(-1);
        }
        prev_a = a;
    }
    if (v.empty()) cout << 0;
    else if (v.size() == 1 && v.front() == 1) cout << 0;
    else {
        int cnt = v.size() + (v.front() == -1) + (v.back() == 1);
        cout << ceil(log2(cnt));
    }
}