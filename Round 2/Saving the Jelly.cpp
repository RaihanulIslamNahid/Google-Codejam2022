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

const int N = 1010;
int n;
ll g[N][N];
ll mx[N];
ll a[N][2], b[N][2];
pli ord[N][N];
int mt[N];
bool used[N];
bool ux[N], uy[N];
int pos[N];

ll sqr(ll x) {
	return x * x;
}

bool dfs(int x) {
	if (used[x]) return false;
	used[x] = 1;
	for (int y = 0; y < n; y++) {
		if (g[x][y] > mx[x]) continue;
		if (mt[y] == -1) {
			mt[y] = x;
			return true;
		}
	}
	for (int y = 0; y < n; y++) {
		if (g[x][y] > mx[x]) continue;
		if (dfs(mt[y])) {
			mt[y] = x;
			return true;
		}
	}
	return false;
}
void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lld%lld", &a[i][0], &a[i][1]);
	scanf("%lld%lld", &b[n][0], &b[n][1]);
	for (int i = 0; i < n; i++)
		scanf("%lld%lld", &b[i][0], &b[i][1]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++)
			g[i][j] = sqr(a[i][0] - b[j][0]) + sqr(a[i][1] - b[j][1]);
		mx[i] = g[i][n];
	}
	for (int i = 0; i < n; i++) {
		mt[i] = -1;
		used[i] = false;
	}
	for (int i = 0; i < n; i++) {
		if (!dfs(i)) {
			printf("IMPOSSIBLE\n");
			return;
		}
		for (int j = 0; j < n; j++)
			used[j] = 0;
	}
	printf("POSSIBLE\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			ord[i][j] = mp(g[i][j], j);
		sort(ord[i], ord[i] + n);
		pos[i] = 0;
	}
	for (int i = 0; i < n; i++)
		ux[i] = uy[i] = false;
	for (int it = 0; it < n; it++) {
		int v = 0;
		while(ux[v]) v++;
		for (int i = 0; i < n; i++)
			used[i] = 0;
		while(!used[v]) {
			used[v] = 1;
			while(uy[ord[v][pos[v]].second]) pos[v]++;
			v = mt[ord[v][pos[v]].second];
		}
		int V = v;
		do {
			int y = ord[v][pos[v]].second;
			int x = mt[y];
			mt[y] = v;
			v = x;
		} while(v != V);
		int y = ord[v][pos[v]].second;
		printf("%d %d\n", v + 1, y + 2);
		ux[v] = 1;
		uy[y] = 1;
	}
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: ", i);
		solve();
	}

	return 0;
}
