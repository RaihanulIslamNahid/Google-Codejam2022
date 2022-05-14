#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) {fprintf(stderr, __VA_ARGS__);fflush(stderr);}
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

const ll INF = (ll)1e18;
const int N = 200200;
int n;
vector<pli> a[2];
ll C;
ll dp[N];
int prv[N];
int lst[N];
ll pref[N][2];

ll solve(vector<pli> b) {
	sort(all(b));
	n = (int)b.size();
	for (int i = 0; i <= n; i++) {
		prv[i] = -1;
		dp[i] = INF;
	}
	pref[0][0] = pref[0][1] = 0;
	for (int i = 0; i < n; i++) {
		pref[i + 1][0] = pref[i][0];
		pref[i + 1][1] = pref[i][1];
		pref[i + 1][b[i].second] += b[i].first;
	}
	int bal = n;
	for (int i = 0; i <= 2 * n; i++)
		lst[i] = -1;
	lst[bal] = 0;
	for (int i = 0; i < n; i++) {
		bal += 1 - 2 * b[i].second;
		prv[i + 1] = lst[bal];
		lst[bal] = i + 1;
	}
	dp[n] = 0;
	for (int i = n; i > 0; i--) {
		dp[i - 1] = min(dp[i - 1], dp[i] + b[i - 1].first);
		if (i >= 2) dp[i - 2] = min(dp[i - 2], dp[i] + b[i - 1].first + C);
		if (prv[i] != -1) dp[prv[i]] = min(dp[prv[i]], dp[i] + max(pref[i][0] - pref[prv[i]][0], pref[i][1] - pref[prv[i]][1]));
	}
	return dp[0];
}

ll solve() {
	scanf("%d%lld", &n, &C);
	a[0].clear(); a[1].clear();
	while(n--) {
		ll x;
		int y;
		scanf("%lld%d", &x, &y);
		if (x > 0) {
			a[0].push_back(mp(x * 2, y));
		} else {
			a[1].push_back(mp(-x * 2, y));
		}
	}
	return solve(a[0]) + solve(a[1]);
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: %lld\n", i, solve());
	}

	return 0;
}
