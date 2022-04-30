#ifndef CLASS_MODINT
#define CLASS_MODINT

#include <cstdint>

template <std::uint32_t mod>
class modint {
private:
	std::uint32_t n;
public:
	modint() : n(0) {};
	modint(std::int64_t n_) : n((n_ >= 0 ? n_ : mod - (-n_) % mod) % mod) {};
	static constexpr std::uint32_t get_mod() { return mod; }
	std::uint32_t get() const { return n; }
	bool operator==(const modint& m) const { return n == m.n; }
	bool operator!=(const modint& m) const { return n != m.n; }
	modint& operator+=(const modint& m) { n += m.n; n = (n < mod ? n : n - mod); return *this; }
	modint& operator-=(const modint& m) { n += mod - m.n; n = (n < mod ? n : n - mod); return *this; }
	modint& operator*=(const modint& m) { n = std::uint64_t(n) * m.n % mod; return *this; }
	modint operator+(const modint& m) const { return modint(*this) += m; }
	modint operator-(const modint& m) const { return modint(*this) -= m; }
	modint operator*(const modint& m) const { return modint(*this) *= m; }
	modint inv() const { return (*this).pow(mod - 2); }
	modint pow(std::uint64_t b) const {
		modint ans = 1, m = modint(*this);
		while (b) {
			if (b & 1) ans *= m;
			m *= m;
			b >>= 1;
		}
		return ans;
	}
};

#endif // CLASS_MODINT

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
using mint = modint<1000000007>;

int main() {
    const int LIMIT = 500000;
    vector<mint> fact(LIMIT + 1);
    fact[0] = 1;
    for (int i = 1; i <= LIMIT; i++) {
        fact[i] = fact[i - 1] * i;
    }
    vector<mint> factinv(LIMIT + 1);
    factinv[LIMIT] = fact[LIMIT].inv();
    for (int i = LIMIT - 1; i >= 0; i--) {
        factinv[i] = factinv[i + 1] * (i + 1);
    }
    function<mint(int, int)> comb = [&](int n, int r) {
        return fact[n] * factinv[r] * factinv[n - r];
    };
    int Q;
    cin >> Q;
    for (int testcase = 1; testcase <= Q; testcase++) {
        int M, K;
        cin >> M >> K;
        vector<mint> b(M / 2 + 1);
        b[0] = mint(1);
        mint sum = 0;
        for (int i = 1; i <= M / 2; i++) {
            sum += 2 * M - 4 * i + 1;
            b[i] = b[i - 1] * (M - 2 * i + 2) * (M - 2 * i + 1) * mint(2).inv() * sum.inv();
        }
        mint ans = 0;
        for (int i = K; i <= M / 2; i++) {
            mint sub = b[i] * comb(i, K);
            if ((i - K) % 2 == 0) {
                ans += sub;
            }
            else {
                ans -= sub;
            }
        }
        cout << "Case #" << testcase << ": " << ans.get() << endl;
    }
    return 0;
}