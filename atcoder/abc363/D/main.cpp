//
// Created by Kamil Tokarski on 20/07/2024.
//

#include <bits/stdc++.h>

using ll = long long;

ll count_palindroms_of_length(ll length) {
    ll res = 1;
    for(ll i = 0; i < (length) / 2; ++i) {
        if (i == 0)
            res *= 9;
        else
            res *= 10;
    }

    if (length % 2)
        res *= 10;
    return res;
}


std::string findNthNumber(ll N, ll K, ll AK) {
    std::cerr << "N: " << N << " K: " << K << std::endl;
    // Handle invalid input (N or K <= 0)
    if (N <= 0 || K <= 0) {
        return "-1";
    }

    auto powlong = [](ll A, ll B) {
        ll res = 1;
        for(auto i = 1; i < B; ++i)
            res *= A;
        return res;
    };

    // Calculate the first number with length K (base case)
    ll firstNumber = ((AK == 1) ? 0 : 1);
    for(auto i = 0; i < (K - 1); ++i)
        firstNumber *= 10;
    std::cerr << firstNumber << std::endl;

    // Convert the calculated number to string and return
    return std::to_string(firstNumber + N - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll N;
    std::cin >> N;

    int i;
    ll sum = 0;
    ll sumN = N;
    for(i = 1; true; ++i) {
        auto count = count_palindroms_of_length(i);
        if (sumN - count <= 0) {
            break;
        }
        sumN -= count;
        std::cerr << i << " = " << count_palindroms_of_length(i) << " with sum = " << sum << std::endl;
    }

    auto searching_for = sumN;
    std::cerr << "searching for " << searching_for << " th number of length " << i << std::endl;

    if (i == 1) {
        std::cout << findNthNumber(searching_for, i, i) << std::endl;
        return 0;
    }

    std::string number;
    if (i % 2 == 1)
        number = findNthNumber(searching_for, i / 2 + 1, i);
    else
        number = findNthNumber(searching_for, i / 2, i);

    std::cout << number;
    if (i % 2)
        number.pop_back();
    std::reverse(number.begin(), number.end());
    std::cout << number << std::endl;

    return 0;
}