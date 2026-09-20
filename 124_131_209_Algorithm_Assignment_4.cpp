#include <bits/stdc++.h>
using namespace std;

struct ATM
{
    int id;
    string name;
    int cashRequired, benefit;
};

struct Task
{
    int id;
    string name;
    int startTime, finishTime;
};

void atmCashAllocation()
{
    cout << "\n========== ATM CASH ALLOCATION ==========\n";

    int n;
    cout << "Enter number of ATMs: ";
    if (!(cin >> n) || n <= 0) return;

    vector<ATM> atms(n);

    for (int i = 0; i < n; i++)
    {
        atms[i].id = i;

        cout << "\nATM " << i + 1 << " name: ";
        cin >> ws;
        getline(cin, atms[i].name);

        cout << "Cash required: ";
        cin >> atms[i].cashRequired;

        cout << "Service benefit: ";
        cin >> atms[i].benefit;
    }

    int capacity;
    cout << "\nEnter total available cash: ";
    if (!(cin >> capacity) || capacity < 0) return;

    if (1LL * (n + 1) * (capacity + 1) > 20000000)
    {
        cout << "Input too large.\n";
        return;
    }

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        int cash = atms[i - 1].cashRequired;
        int benefit = atms[i - 1].benefit;

        for (int c = 0; c <= capacity; c++)
        {
            dp[i][c] = dp[i - 1][c];

            if (cash <= c)
                dp[i][c] = max(dp[i][c], benefit + dp[i - 1][c - cash]);
        }
    }

    vector<int> selected;
    int remaining = capacity;

    for (int i = n; i >= 1; i--)
    {
        if (dp[i][remaining] != dp[i - 1][remaining])
        {
            selected.push_back(i - 1);
            remaining -= atms[i - 1].cashRequired;
        }
    }

    reverse(selected.begin(), selected.end());

    int totalCashUsed = 0;

    cout << "\n========== RESULT ==========\n";
    cout << "Maximum Service Benefit: " << dp[n][capacity] << "\n";

    cout << "\nSelected ATMs:\n";

    for (int index : selected)
    {
        cout << atms[index].name
             << " | Cash: " << atms[index].cashRequired
             << " | Benefit: " << atms[index].benefit << "\n";

        totalCashUsed += atms[index].cashRequired;
    }

    cout << "\nTotal Cash Used: " << totalCashUsed << "\n";
    cout << "Remaining Cash: " << capacity - totalCashUsed << "\n";
}


void shortestServiceRoute()
{
    cout << "\n========== DIJKSTRA ROUTING ==========\n";

    int n;
    cout << "Enter number of locations: ";
    if (!(cin >> n) || n <= 0) return;

    vector<string> locationName(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Location " << i << ": ";
        cin >> ws;
        getline(cin, locationName[i]);
    }

    int edges;
    cout << "\nEnter number of roads: ";
    if (!(cin >> edges) || edges < 0) return;

    vector<vector<pair<int, int>>> graph(n);

    cout << "Enter source destination travel_time:\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 0 || u >= n || v < 0 || v >= n || w < 0)
        {
            cout << "Invalid road.\n";
            return;
        }

        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    cout << "\nLocations:\n";
    for (int i = 0; i < n; i++)
        cout << i << " = " << locationName[i] << "\n";

    int source, destination;

    cout << "\nEnter source: ";
    cin >> source;

    cout << "Enter destination: ";
    cin >> destination;

    if (source < 0 || source >= n || destination < 0 || destination >= n)
    {
        cout << "Invalid source or destination.\n";
        return;
    }

    const long long INF = LLONG_MAX / 4;

    vector<long long> dist(n, INF);
    vector<int> parent(n, -1);

    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        long long currentDistance = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (currentDistance != dist[node]) continue;
        if (node == destination) break;

        for (auto edge : graph[node])
        {
            int nextNode = edge.first;
            int weight = edge.second;
            long long newDistance = dist[node] + weight;

            if (newDistance < dist[nextNode])
            {
                dist[nextNode] = newDistance;
                parent[nextNode] = node;
                pq.push({newDistance, nextNode});
            }
        }
    }

    if (dist[destination] == INF)
    {
        cout << "\nNo route exists.\n";
        return;
    }

    vector<int> path;

    for (int current = destination; current != -1; current = parent[current])
        path.push_back(current);

    reverse(path.begin(), path.end());

    cout << "\n========== RESULT ==========\n";
    cout << "Minimum Travel Time: " << dist[destination] << " minutes\n";
    cout << "Shortest Route: ";

    for (int i = 0; i < path.size(); i++)
    {
        cout << locationName[path[i]];
        if (i + 1 < path.size()) cout << " -> ";
    }

    cout << "\n";
}


void scheduleServiceTasks()
{
    cout << "\n========== GREEDY SCHEDULING ==========\n";

    int n;
    cout << "Enter number of service tasks: ";
    if (!(cin >> n) || n <= 0) return;

    vector<Task> tasks(n);

    for (int i = 0; i < n; i++)
    {
        tasks[i].id = i;

        cout << "\nTask " << i + 1 << " name: ";
        cin >> ws;
        getline(cin, tasks[i].name);

        cout << "Start time: ";
        cin >> tasks[i].startTime;

        cout << "Finish time: ";
        cin >> tasks[i].finishTime;

        if (tasks[i].finishTime <= tasks[i].startTime)
        {
            cout << "Invalid task time.\n";
            return;
        }
    }

    sort(tasks.begin(), tasks.end(), [](Task a, Task b)
    {
        if (a.finishTime == b.finishTime)
            return a.startTime < b.startTime;

        return a.finishTime < b.finishTime;
    });

    vector<Task> selected;
    int lastFinish = INT_MIN;

    for (auto task : tasks)
    {
        if (task.startTime >= lastFinish)
        {
            selected.push_back(task);
            lastFinish = task.finishTime;
        }
    }

    cout << "\n========== OPTIMAL SERVICE SCHEDULE ==========\n";

    for (auto task : selected)
        cout << task.name << " | " << task.startTime << " - " << task.finishTime << "\n";

    cout << "\nMaximum Compatible Tasks: " << selected.size() << "\n";
}


void showAbout()
{
    cout << "\n========== ALGORITHMS ==========\n";
    cout << "1. Dynamic Programming -> ATM Cash Allocation\n";
    cout << "2. Dijkstra -> Shortest Service Route\n";
    cout << "3. Greedy Activity Selection -> Service Scheduling\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true)
    {
        cout << "\n========================================\n";
        cout << " ATM BANKING MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Optimize ATM Cash Allocation\n";
        cout << "2. Find Shortest Service Route\n";
        cout << "3. Schedule ATM Service Tasks\n";
        cout << "4. About Algorithms\n";
        cout << "5. Exit\n";
        cout << "========================================\n";

        int choice;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) return 0;

        if (choice == 1)
            atmCashAllocation();

        else if (choice == 2)
            shortestServiceRoute();

        else if (choice == 3)
            scheduleServiceTasks();

        else if (choice == 4)
            showAbout();

        else if (choice == 5)
        {
            cout << "\nProgram terminated.\n";
            break;
        }

        else
            cout << "\nInvalid choice.\n";
    }

    return 0;
}