# ATM Banking Management System

A simple C++ project for **CSE 4403 (Algorithms)** that applies:

- **Dynamic Programming / 0-1 Knapsack** for ATM cash allocation
- **Dijkstra's Algorithm** for shortest service routing
- **Greedy Activity Selection** for ATM service scheduling

## Test Case 1

### Input
```text
1
4
ATM-A
6
90
ATM-B
4
60
ATM-C
5
75
ATM-D
3
50
10
5
```

### Output
```text
Maximum Service Benefit: 150

Selected ATMs:
ATM-A | Cash: 6 | Benefit: 90
ATM-B | Cash: 4 | Benefit: 60

Total Cash Used: 10
Remaining Cash: 0
```

## Test Case 2

### Input
```text
2
5
Cash Depot
Intersection A
Intersection B
Intersection C
ATM-D
7
0 1 4
0 2 2
2 1 1
1 3 5
2 3 8
3 4 2
1 4 10
0
4
5
```

### Output
```text
Minimum Travel Time: 10 minutes

Shortest Route:
Cash Depot -> Intersection B -> Intersection A -> Intersection C -> ATM-D
```
