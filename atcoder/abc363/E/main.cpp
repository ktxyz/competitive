//
// Created by Kamil Tokarski on 20/07/2024.
//

#include <bits/stdc++.h>

constexpr int MAXN = 1e3 + 1;
constexpr int MAXA = 1e5 + 1;
constexpr int INF = 1e5;
int grid[MAXN][MAXN];
int minNeigh[MAXN][MAXN];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

int is_valid(int x, int y, int W, int H) {
    return (x >= 0 && y >= 0 && x < W && y < H);
}

using coord = std::pair<int, int>;
std::vector<coord> coastLine[MAXN];

bool removed[MAXN][MAXN];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int H, W, Y;
    std::cin >> H >> W >> Y;

    std::vector<std::tuple<int, int, int>> sortedByWidth;
    for(auto y = 0; y < H; ++y) {
        for(auto x = 0; x < W; ++x) {
            std::cin >> grid[y][x];

            if (y == 0 || y == H - 1 || x == 0 || x == W - 1)
                removed[y][x] = true,
                coastLine[grid[y][x]].emplace_back(y, x);
        }
    }

    int area = H * W;
    for(auto i = 1; i <= Y; ++i) {
        std::queue<coord> Q;
        for(auto &c : coastLine[i])
            removed[c.first][c.second] = true,
            Q.push(c);

        while(!Q.empty()) {
            auto [y, x] = Q.front(); Q.pop();
            removed[y][x] = true;
            area -= 1;

            for(auto d = 0; d < 4; ++d) {
                auto ny = y + dy[d];
                auto nx = x + dx[d];

                if (!is_valid(nx, ny, W, H))
                    continue;
                if (removed[ny][nx])
                    continue;

                removed[ny][nx] = true;
                if (grid[ny][nx] <= i)
                    Q.emplace(ny, nx);
                else
                    coastLine[grid[ny][nx]].emplace_back(ny, nx);
            }
        }

        std::cout << area << std::endl;
    }

    return 0;
}