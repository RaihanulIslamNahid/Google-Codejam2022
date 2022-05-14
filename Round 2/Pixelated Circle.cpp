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

const int N = (int)1e5 + 1;
//const int N = (int)1e3 + 1;
ll ans[N + 11];

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	for (ll y = 1; y < N; y++) {
		//if (y % 1000 == 0) eprintf("y = %lld, time = %.5lf\n", y, getCurrentTime());
		ll R = y;
		ll x2y2 = y * y;
		ll R2R = R * R + R;
		for (ll x = 1; x <= y; x++) {
			x2y2 += x + x - 1;
			while(R2R < x2y2) {
				R++;
				R2R += R + R;
			}
			if (R >= N) break;
			ll z = x2y2 - R2R + R;
			if (z > 0) {
				if (z >= y && z <= R + R - y) {
					ans[R] += 1 + (int)(x != y);
				}
			} else {
				z += R + R - 1;
				if (z >= y && z <= R + R - 2 - y) {
					ans[R] += 1 + (int)(x != y);
				}
			}
		}
	}
	for (int i = 1; i <= N; i++)
		ans[i] += ans[i - 1];

	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		int n;
		scanf("%d", &n);
		printf("Case #%d: %lld\n", i, 4 * ans[n]);
	}

	return 0;
}
