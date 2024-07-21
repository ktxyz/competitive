import random


def generate_test_case(num_jobs, num_queries, max_deadline, max_priority):
    deadlines = [random.randint(1, max_deadline) for _ in range(num_jobs)]
    priorities = [random.randint(1, max_priority) for _ in range(num_jobs)]

    queries = []
    for _ in range(num_queries):
        index = random.randint(1, num_jobs)
        day = random.randint(1, max_deadline)
        priority = random.randint(1, max_priority)
        queries.append((index, day, priority))

    return deadlines, priorities, queries


def write_test_case(filename, deadlines, priorities, queries):
    with open(filename, 'w') as f:
        f.write(f"{len(deadlines)} {len(queries)}\n")
        f.write(" ".join(map(str, deadlines)) + "\n")
        f.write(" ".join(map(str, priorities)) + "\n")
        for query in queries:
            f.write(" ".join(map(str, query)) + "\n")


def main():
    num_cases = 10
    num_jobs = 5
    num_queries = 5
    max_deadline = 5
    max_priority = 20

    for i in range(num_cases):
        deadlines, priorities, queries = generate_test_case(num_jobs, num_queries, max_deadline, max_priority)
        write_test_case(f"tests/test_case_{i}.txt", deadlines, priorities, queries)


if __name__ == "__main__":
    main()
