//
// Created by Kamil Tokarski on 13/07/2024.
//
#include <queue>
#include <vector>
#include <iostream>


constexpr int MAXN = 2e5 + 1;

int N;
int TSIZE[MAXN];
std::vector<int> PRE;
std::vector<int> G[MAXN];
int CENTROID;

int rootifyDFS(const int v, const int parent = -1) {
    bool is_centroid = true;
    TSIZE[v] = 1;
    for(auto const &u : G[v]) {
        if (u == parent) continue;
        TSIZE[v] += rootifyDFS(u, v);
        if (TSIZE[u] > N / 2)
            is_centroid = false;
    }

    if (N - TSIZE[v] > N / 2)
        is_centroid = false;

    if (is_centroid)
        CENTROID = v;

    return TSIZE[v];
}

void preDFS(int v, int parent) {
    PRE.emplace_back(v);
    for(const auto& u : G[v])
        if (u != parent)
            preDFS(u, v);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    std::cin >> N;

    for(auto i = 0; i < N - 1; ++i) {
        int v, u;
        std::cin >> v >> u;

        G[v].push_back(u);
        G[u].push_back(v);
    }

    rootifyDFS(1);
    std::cerr << "centroid: " << CENTROID << std::endl;

     preDFS(CENTROID, CENTROID);
     if (PRE.size() % 2)
         PRE.erase(PRE.begin());

     for(auto i = 0; i < N / 2; ++i)
         std::cout << PRE[i] << " " << PRE[i + N / 2] << std::endl;

    return 0;
}
