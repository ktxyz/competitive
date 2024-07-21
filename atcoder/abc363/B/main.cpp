//
// Created by Kamil Tokarski on 20/07/2024.
//

#include <bits/stdc++.h>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, T, P;
    std::cin >> N >> T >> P;

    std::vector<int> time;
    for(int i = 0; i < N; ++i) {
        int l;
        std::cin >> l;

        if (l >= T)
            time.push_back(0);
        else
            time.push_back(T - l);
    }

    std::sort(time.begin(), time.end());

    std::cout << time[P - 1] << std::endl;
    return 0;
}