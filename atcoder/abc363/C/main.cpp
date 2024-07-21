//
// Created by Kamil Tokarski on 20/07/2024.
//

#include <bits/stdc++.h>


std::vector<int> manacher_odd(std::string s) {
    int n = s.size();
    s = "$" + s + "^";
    std::vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = std::max(0, std::min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return std::vector<int>(begin(p) + 1, end(p) - 1);
}

std::vector<int> manacher(const std::string& s) {
    std::string t;
    for(auto c: s) {
        t += std::string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return std::vector<int>(begin(res) + 1, end(res) - 1);
}

bool containsPalindrome(const std::string& s, int length) {
    if (length > s.size()) {
        return false;
    }

    for (int i = 0; i <= s.size() - length; i++) {
        bool isPalindrome = true;
        for (int j = 0; j < length / 2; j++) {
            if (s[i + j] != s[i + length - 1 - j]) {
                isPalindrome = false;
                break;
            }
        }
        if (isPalindrome) {
            return true;
        }
    }

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);


    int N, K;
    std::cin >> N >> K;

    std::string S;
    std::cin >> S;


    int answer = 0;
    std::sort(S.begin(), S.end());
    do {
        if (!containsPalindrome(S, K))
            answer++;
    } while (std::next_permutation(S.begin(), S.end()));

    std::cout << answer << std::endl;
    return 0;
}