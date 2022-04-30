#ifndef CLASS_DISJOINT_SET
#define CLASS_DISJOINT_SET

#include <vector>
#include <cstdint>
#include <cstring>
#include <algorithm>

class disjoint_set {
private:
	typedef std::int32_t value_type;
	std::vector<value_type> val;
public:
	explicit disjoint_set() : val() {};
	explicit disjoint_set(std::size_t n) : val(n, -1) {};
	std::size_t size() const { return val.size(); }
	std::size_t size(std::size_t elem) { return std::size_t(-val[root(elem)]); }
	std::size_t root(std::size_t elem) {
		// path halving
		while (val[elem] >= 0 && val[val[elem]] >= 0) {
			val[elem] = val[val[elem]];
			elem = val[elem];
		}
		return std::size_t(val[elem] >= 0 ? val[elem] : elem);
	}
	void link(std::size_t elemx, std::size_t elemy) {
		elemx = root(elemx);
		elemy = root(elemy);
		if (elemx == elemy) return;
		if (val[elemx] > val[elemy]) {
			std::swap(elemx, elemy);
		}
		val[elemx] += val[elemy];
		val[elemy] = elemx;
	}
	bool connected(std::size_t elemx, std::size_t elemy) {
		return root(elemx) == root(elemy);
	}
};

#endif // CLASS_DISJOINT_SET

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    int Q;
    cin >> Q;
    for (int testcase = 1; testcase <= Q; testcase++) {
        int N;
        cin >> N;
        vector<string> S(N);
        vector<vector<bool> > v(26, vector<bool>(26, false));
        vector<int> indeg(26), outdeg(26);
        for (int i = 0; i < N; i++) {
            cin >> S[i];
            for (int j = 1; j < int(S[i].size()); j++) {
                if (S[i][j - 1] != S[i][j]) {
                    v[S[i][j - 1] - 'A'][S[i][j] - 'A'] = true;
                    indeg[S[i][j] - 'A'] += 1;
                    outdeg[S[i][j - 1] - 'A'] += 1;
                }
            }
        }
        vector<bool> vis(26, false);
        bool valid = true;
        vector<int> ord;
        function<void(int)> dfs = [&](int pos) {
            vis[pos] = true;
            ord.push_back(pos);
            for (int i = 0; i < 26; i++) {
                if (v[pos][i] && !vis[i]) {
                    dfs(i);
                }
                else if (v[pos][i]) {
                    valid = false;
                }
            }
        };
        for (int i = 0; i < 26; i++) {
            if (indeg[i] == 0 && !vis[i]) {
                dfs(i);
            }
        }
        if (!valid || vis != vector<bool>(26, true) || *max_element(indeg.begin(), indeg.end()) >= 2 || *max_element(outdeg.begin(), outdeg.end()) >= 2) {
            cout << "Case #" << testcase << ": IMPOSSIBLE" << endl;
        }
        else {
            vector<int> cnt(26);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < int(S[i].size()); j++) {
                    cnt[S[i][j] - 'A'] += 1;
                }
            }
            cout << "Case #" << testcase << ": ";
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < cnt[ord[i]]; j++) {
                    cout << char(ord[i] + 'A');
                }
            }
            cout << endl;
        }
    }
    return 0;
}