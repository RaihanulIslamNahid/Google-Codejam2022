#include <bits/stdc++.h>
using namespace std;

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    int n;
    cin >> n;
    vector<int> a(n), prefmax(n), suffmax(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    prefmax[0] = a[0];
    for (int i = 1; i < n; i++) {
      prefmax[i] = max(prefmax[i-1], a[i]);
    }
    suffmax[n-1] = a[n-1];
    for (int i = n-2; i >= 0; i--) {
      suffmax[i] = max(suffmax[i+1], a[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] >= prefmax[i] || a[i] >= suffmax[i]) {
        ans++;
      }
    }
    cout << "Case #" << tc << ": " << ans << '\n';
  }
}
