//
// Created by Kamil Tokarski on 20/07/2024.
//

#include <bits/stdc++.h>

using ll = long long;

std::unordered_map<ll, std::string> cache;

std::string find_palindrome(ll N) {
    if (cache.count(N))
        return cache[N];
    if (N == 0)
        return "";

    static auto rev = [](const ll number) {
        std::string s = std::to_string(number);
        std::reverse(s.begin(), s.end());
        return s;
    };

    const auto sN = std::to_string(N);
    const auto revsN = rev(N);

    if (sN.find('0') == std::string::npos && sN == revsN)
        return cache[N] = sN;

    for(ll i = 2; i * i <= N; ++i) {
        if (N % i != 0) continue;
        auto sI = std::to_string(i);
        if (sI.find('0') != std::string::npos) continue;
        const auto revsI = rev(i);
        const auto revI = std::stoll(revsI);
        if ((N / i) % revI) continue;
        auto find_pal  = find_palindrome(N / (i * revI));
        if (find_pal.empty()) continue;;

        auto answer = sI;
        answer += '*';
        answer += find_pal;
        answer += '*';
        answer += revsI;
        return cache[N] = answer;
    }

    return cache[N] = "";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll N;
    std::cin >> N;

    if (const auto answer = find_palindrome(N); !answer.empty())
        std::cout << answer << std::endl;
    else
        std::cout << "-1" << std::endl;

    return 0;
}