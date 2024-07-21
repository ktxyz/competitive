//
// Created by Kamil Tokarski on 20/07/2024.
//

#include <bits/stdc++.h>

using llong = long long;
constexpr llong INF = 1e12;

struct Task {
    llong deadline;
    llong reward;

    Task(const int deadline, const int reward) : deadline(deadline), reward(reward) {}
    bool operator<(const Task& other) const {
        if (other.reward == reward) return deadline < other.deadline;
        return reward < other.reward;
    }
};

struct Query {
    size_t idx;
    Task task;

    Query(const int idx, const int deadline, const int reward) : idx(idx), task(deadline, reward) {}
};

std::vector<llong> calc_answer_rec(int N, std::vector<Task> tasks, std::vector<Query> queries) {
    auto T = tasks.size();
    auto Q = queries.size();

    std::vector<bool> is_task_volatile(T, false);
    for(const auto &q : queries)
        is_task_volatile[q.idx] = true;

    std::vector<std::vector<size_t>> day_tasks(N);
    for(auto i = 0; i < T; ++i)
        if (tasks[i].deadline < N)
            day_tasks[tasks[i].deadline].push_back(i);
    for(const auto &q : queries)
        if (q.task.deadline < N)
            day_tasks[q.task.deadline].push_back(q.idx);

    llong absolute_reward = 0;
    std::vector<bool> day_active(N, true);
    std::priority_queue<std::pair<llong, int>> PQ;
    std::vector<bool> task_executed(T, false);

    for(auto day = 0; day < N; ++day) {
        for(const auto &task_idx : day_tasks[day])
            PQ.emplace((is_task_volatile[task_idx] ? INF : tasks[task_idx].reward), task_idx);

        if (PQ.empty()) {
            day_active[day] = false;
            continue;
        }

        const auto [reward, task_idx] = PQ.top(); PQ.pop();
        if (is_task_volatile[task_idx])
            continue;

        absolute_reward += reward;
        task_executed[task_idx] = true;
    }

    if (Q == 0)
        return {absolute_reward};

    while(!PQ.empty()) PQ.pop();

    for(auto day = 0; day < N; ++day) {
        for(const auto &task_idx : day_tasks[day])
            if (!is_task_volatile[task_idx])
                PQ.emplace(tasks[task_idx].reward, task_idx);

        if (PQ.empty())
            continue;

        const auto task_idx = PQ.top().second; PQ.pop();

        if (task_executed[task_idx])
            day_active[day] = false;
    }

    while(!PQ.empty()) {
        const auto task_idx = PQ.top().second; PQ.pop();
        task_executed[task_idx] = true;
    }

    std::vector<int> remaped_active_days(N + 1, 0);
    for(auto day = 0; day < N; ++day) {
        remaped_active_days[day + 1] = remaped_active_days[day] + day_active[day];
    }

    std::vector<Task> volatile_tasks;
    std::vector<size_t> task_mapping(T, -1);
    for(auto task_idx = 0; task_idx < T; ++task_idx) {
        if (task_executed[task_idx]) continue;

        const auto &task = tasks[task_idx];
        task_mapping[task_idx] = volatile_tasks.size();
        volatile_tasks.emplace_back(remaped_active_days[task.deadline], task.reward);
    }

    for(auto &q : queries) {
        q.idx = task_mapping[q.idx],
        q.task.deadline = remaped_active_days[q.task.deadline];
    }

    const auto half_size = Q / 2;
    auto left_batch = calc_answer_rec(remaped_active_days[N], volatile_tasks,
                                                    std::vector<Query>(queries.begin(), queries.begin() + half_size));

    for(auto qidx = 0; qidx <= half_size; ++qidx) {
        volatile_tasks[queries[qidx].idx] = queries[qidx].task;
    }

    auto right_batch = calc_answer_rec(remaped_active_days[N], volatile_tasks,
                                                    std::vector<Query>(queries.begin() + (half_size + 1), queries.end()));

    auto answer = left_batch;
    answer.insert(answer.end(), right_batch.begin(), right_batch.end());

    for(auto &a : answer)
        a += absolute_reward;

    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;

    std::vector<Task> tasks;
    for(auto i = 0; i < N; ++i) {
        int d;
        std::cin >> d;

        tasks.emplace_back(N - d, 0);
    }

    for(auto i = 0; i < N; ++i)
        std::cin >> tasks[i].reward;

    std::vector<Query> queries;
    for(auto i = 0; i < Q; ++i) {
        int c, x, y;
        std::cin >> c >> x >> y;

        queries.emplace_back(--c, N - x, y);
    }

    const auto answer = calc_answer_rec(N, tasks, queries);
    std::cerr << answer[0] << std::endl;
    for(auto i = 1; i <= Q; ++i)
        std::cout << answer[i] << std::endl;

    return 0;
}
