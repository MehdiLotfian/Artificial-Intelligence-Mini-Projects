#include <queue>
#include<bits/stdc++.h>
#include <algorithm>
#define N 20

using namespace std;
int n, m;

typedef struct node node;
struct node {
    vector<int> neighbors;
};

typedef struct state state;
struct state {
    int g;
    int h;
    int zero_index;
    int labels[N] = {0};
};

struct compare_a {
    bool operator()(state const& s1, state const& s2){
        return ((s1.g + s1.h) > (s2.g + s2.h)) || (((s1.g + s1.h) == (s2.g + s2.h)) && (s1.g < s2.g)) ;
    }
};

string convertArrayToString(const int arr[], int size) {
    string s = "";
    for (int i = 0; i < size; i++)
        s += to_string(arr[i]);
    return s;
}

int calculate_h (int distances [][N], const int labels[]) {
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (labels[i] != 0)
            h += distances[i][labels[i]];
    }
    return h;
}

int find_zero_index(const int list[], int size) {
    for (int i = 0; i < size; i++) {
        if (list[i] == 0)
            return i;
    }
    return -1;
}

int find_min_moves(int distances [][N], int labels[], node graph[]) {
    priority_queue<state, vector<state>, compare_a> states_min_heap;
    hash<string> hasher;
    unordered_set <size_t> used_states;
    state s0;
    state current_state = s0;
    copy(labels, labels + n, current_state.labels);
    current_state.g = 0;
    current_state.h = calculate_h(distances, current_state.labels);
    current_state.zero_index = find_zero_index(current_state.labels, n);
    while (current_state.h != 0) {
        int neighbors_size = graph[current_state.zero_index].neighbors.size();
        for (int i = 0; i < neighbors_size; i++) {
            state s_temp;
            copy(current_state.labels, current_state.labels + n, s_temp.labels);
            s_temp.labels[current_state.zero_index] =
                    current_state.labels[graph[current_state.zero_index].neighbors[i]];
            s_temp.labels[graph[current_state.zero_index].neighbors[i]] = 0;
            s_temp.g = current_state.g + 1;
            s_temp.h = calculate_h(distances, s_temp.labels);
            s_temp.zero_index = graph[current_state.zero_index].neighbors[i];
            states_min_heap.push(s_temp);
        }
        while (used_states.find(hasher(convertArrayToString(states_min_heap.top().labels, n))) != used_states.end())
            states_min_heap.pop();
        current_state = states_min_heap.top();
        states_min_heap.pop();
        used_states.insert(hasher(convertArrayToString(current_state.labels, n)));
    }
    return current_state.g;
}

void find_shortest_paths(int distances [][N], node graph[]) {
    for (int i = 0; i < n; i++) {
        bool visited [N] = {false};
        list<int> queue;

        visited[i] = true;
        queue.push_back(i);
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop_front();
            for (auto neighbor : graph[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push_back(neighbor);
                    distances[i][neighbor] = distances[i][current] + 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int distances [N][N] = {0};
    node graph [n];
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        graph[a].neighbors.push_back(b);
        graph[b].neighbors.push_back(a);
    }
    find_shortest_paths(distances, graph);

    int labels[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &labels[i]);

    printf("%d", find_min_moves(distances, labels, graph));
    return 0;
}