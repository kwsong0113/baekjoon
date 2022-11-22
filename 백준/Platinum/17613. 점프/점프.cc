#include <bits/stdc++.h>
using namespace std;
int t, x, y;

int maxJ(int x, int y) {
    if (x == 0 && y == 0) return 0;
    int ans = 0;
    for (int k = 1; k <= 29; ++k) {
        int l = (1 << k) - 1, r = (1 << (k + 1)) - 2;
        if (x > r) continue;
        if (y < l) break;
        if (l >= x && r <= y) ans = max(ans, 1 + k * (k + 1) / 2);
        else {
            int p = max(x, l), q = min(y, r);
            ans = max(ans, maxJ(p - l, q - l) + k);
        }
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> x >> y;
        cout << maxJ(x, y) << "\n";
    }
    
}