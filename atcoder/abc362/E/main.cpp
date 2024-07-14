//
// Created by Kamil Tokarski on 13/07/2024.
//
#include <vector>
#include <iostream>
#include <unordered_map>


using ll = long long;
constexpr int MAXN = 80 + 1;
constexpr ll MOD = 998244353;

std::unordered_map<ll, ll> DP[MAXN][MAXN];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int N;
    std::vector<int> values;

    std::cin >> N;
    for(auto i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        values.push_back(a);
    }

    for(auto i = 0; i < N; ++i) {
        for(auto j = 0; j < i; ++j) {
            auto const diff = values[i] - values[j];
            for(auto k = 0; k <= N; ++k) {
                DP[i][k + 1][diff] = (DP[i][k + 1][diff] + DP[j][k][diff]) % MOD;
            }
            DP[i][2][diff] += 1;
        }
    }

    std::cout << N << " ";
    for(auto k = 2; k <= N; ++k) {
        ll sum = 0;
        for (auto i = 0; i < N; ++i)
            for(auto &[key, val] : DP[i][k])
                sum = (sum + val) % MOD;
        std::cout << sum << " ";
    }

    return 0;
}
