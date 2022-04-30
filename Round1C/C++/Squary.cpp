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
        int N, K;
        cin >> N >> K;
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        long long alpha = 0, beta = 0;
        for (int i = 0; i < N; i++) {
            alpha += A[i];
            for (int j = i + 1; j < N; j++) {
                beta += 1LL * A[i] * A[j];
            }
        }
        long long INF = (1LL << 60);
        vector<long long> answer(K, INF);
        if (K == 1) {
            if (alpha == 0) {
                if (beta == 0) {
                    answer[0] = 0;
                }
            }
            else {
                if (abs(beta) % abs(alpha) == 0) {
                    answer[0] = -beta / alpha;
                }
            }
        }
        else {
            answer[0] = -alpha + 1;
            answer[1] = -alpha + (alpha * alpha - beta);
            for (int i = 2; i < K; i++) {
                answer[i] = 0;
            }
        }
        if (answer == vector<long long>(K, INF)) {
            cout << "Case #" << testcase << ": IMPOSSIBLE" << endl;
        }
        else {
            cout << "Case #" << testcase << ":";
            for (int i = 0; i < K; i++) {
                cout << ' ' << answer[i];
            }
            cout << endl;
        }
    }
    return 0;
}