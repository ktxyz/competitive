//
// Created by Kamil Tokarski on 13/07/2024.
//
#include <vector>
#include <iostream>
#include <string>

constexpr size_t ALPH = 256;

std::vector<int> sort_cyclic_shifts(const std::string &s) {
    std::vector<int> perm_idx(s.size());
    std::vector<int> eq_class(s.size());
    std::vector<int> count(std::max(s.size(), ALPH), 0);

    // 0-th iteration
    for (const auto &c: s)
        count[c]++;
    for (auto i = 1; i < ALPH; ++i)
        count[i] += count[i - 1];
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
        perm_idx[--count[s[i]]] = i;
    int classes = 1;
    eq_class[perm_idx[0]] = 0;
    for (size_t i = 1; i < s.size(); ++i) {
        if (s[perm_idx[i]] != s[perm_idx[i - 1]])
            classes++;
        eq_class[perm_idx[i]] = classes - 1;
    }

    // k-th iteration
    std::vector<int> perm_n(s.size());
    std::vector<int> eq_class_n(s.size());
    for (int h = 0; (1 << h) < static_cast<int>(s.size()); ++h) {
        for (size_t i = 0; i < s.size(); ++i) {
            perm_n[i] = perm_idx[i] - (1 << h);
            if (perm_n[i] < 0)
                perm_n[i] += static_cast<int>(s.size());
        }

        std::fill(count.begin(), count.end(), 0);

        for (size_t i = 0; i < s.size(); ++i)
            count[eq_class[perm_n[i]]]++;
        for (size_t i = 1; i < static_cast<size_t>(classes); ++i)
            count[i] += count[i - 1];
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
            perm_idx[--count[eq_class[perm_n[i]]]] = perm_n[i];
        eq_class_n[perm_idx[0]] = 0;

        classes = 1;
        for (size_t i = 1; i < s.size(); ++i) {
            auto curr = std::make_pair(eq_class[perm_idx[i]], eq_class[(perm_idx[i] + (1 << h)) % s.size()]);
            auto prev = std::make_pair(eq_class[perm_idx[i - 1]], eq_class[(perm_idx[i - 1] + (1 << h)) % s.size()]);

            if (curr != prev)
                ++classes;

            eq_class_n[perm_idx[i]] = classes - 1;
        }
        eq_class.swap(eq_class_n);
    }

    return perm_idx;
}

std::vector<int> calc_suffix_array(const std::string &s) {
    std::string s_mod = s + "$";
    auto shifts = sort_cyclic_shifts(s_mod);
    shifts.erase(shifts.begin());
    return shifts;
}

int binary_search(const std::string &text, const std::vector<int> &suffix_array, const std::string &pattern) {
    int low = -1, high = static_cast<int>(text.size());
    while (high - low > 1) {
        const int mid = (low + high) / 2;
        if (const std::string suffix = text.substr(suffix_array[mid], pattern.size()); pattern <= suffix) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return high;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;

    const auto suffix_array = calc_suffix_array(text);

    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        std::string query;
        std::cin >> query;
        const int left = binary_search(text, suffix_array, query);
        const int right = binary_search(text, suffix_array, query + "~");
        std::cout << (right - left) << "\n";
    }

    return 0;
}
