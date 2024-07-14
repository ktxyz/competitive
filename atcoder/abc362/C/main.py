def find_sequence(N, intervals):
    sum_min = sum(L for L, R in intervals)
    sum_max = sum(R for L, R in intervals)

    if sum_min > 0 or sum_max < 0:
        return "No"

    X = [L for L, R in intervals]
    current_sum = sum_min

    print('Yes')
    if current_sum < 0:
        for i in range(N):
            L, R = intervals[i]
            if current_sum == 0:
                break
            max_increase = R - L
            increase = min(-current_sum, max_increase)
            X[i] += increase
            current_sum += increase
    elif current_sum > 0:
        for i in range(N):
            L, R = intervals[i]
            if current_sum == 0:
                break
            max_decrease = X[i] - L
            decrease = min(current_sum, max_decrease)
            X[i] -= decrease
            current_sum -= decrease

    return " ".join(map(str, X))


N = int(input())
intervals = []
for i in range(N):
    L, R = map(int, input().split())
    intervals += [(L, R)]

print(find_sequence(N, intervals))
