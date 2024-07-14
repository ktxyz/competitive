//
// Created by Kamil Tokarski on 13/07/2024.
//
#include <iostream>
#include <vector>
#include <queue>


using ll = long long;
constexpr ll INF = 1e18;
constexpr int MAXN = 2e5 + 1;

struct Edge {
    int u;
    ll w;
};

std::vector<Edge> G[MAXN];

std::vector<ll> dist(MAXN, INF);
std::vector<ll> weight(MAXN, 0);

void dijkstra(int start) {
    using P = std::pair<ll, int>;
    std::priority_queue<P, std::vector<P>, std::greater<>> pq;
    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (d > dist[v]) continue;

        for (auto &edge : G[v]) {
            int u = edge.u;
            ll weight = edge.w;

            if (dist[v] + weight < dist[u]) {
                dist[u] = dist[v] + weight;
                pq.emplace(dist[u], u);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;

    for(auto i = 0; i < N; ++i) {
        int a;
        std::cin >> a;
        weight[i + 1] = a;
    }

    for(auto i = 0; i < M; ++i) {
        int a, b, w;
        std::cin >> a >> b >> w;

        G[a].push_back({b, w + weight[a]});
        G[b].push_back({a, w + weight[b]});
    }

    // Run Dijkstra from V=1
    dijkstra(1);

    for(auto i = 2; i <= N; ++i)
        std::cout << dist[i] + weight[i] << " ";
    std::cout << std::endl;

    return 0;
}