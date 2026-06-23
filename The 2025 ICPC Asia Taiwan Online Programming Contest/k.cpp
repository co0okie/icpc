#include <bits/stdc++.h>
using namespace std;
#define ll long long

using node_t = uint32_t;
using stone_t = node_t;
using capacity_t = node_t;
using level_t = int32_t;
using edge_t = uint32_t;

const int MAX_N = 500;
const int MAX_NODES = MAX_N * MAX_N + 2 * MAX_N + 2;
const int MAX_EDGES = MAX_N * MAX_N * 6 * 2;

int stones[MAX_NODES];
list<edge_t> adj[MAX_NODES];
level_t level[MAX_NODES];

node_t nodes_size = 0;

node_t to_node[MAX_EDGES];
capacity_t capacity[MAX_EDGES];
edge_t reverse_edge[MAX_EDGES];

edge_t edges_size = 0;

node_t super_source;
node_t super_sink;

int bfs_count = 0;
int dfs_count = 0;
uint64_t dfs_depth = 0;

edge_t add_edge(node_t from, node_t to, capacity_t c) {
    edge_t edge = edges_size++, r_edge = edges_size++;
    adj[from].push_back(edge);
    capacity[edge] = c;
    reverse_edge[edge] = r_edge;
    to_node[edge] = to;
    adj[to].push_back(r_edge);
    capacity[r_edge] = 0;
    reverse_edge[r_edge] = edge;
    to_node[r_edge] = from;
    return edge;
}

bool bfs() {
    ranges::fill_n(level, nodes_size, -1);
    queue<node_t> frontier;
    level[super_source] = 0;
    frontier.push(super_source);
    while (!frontier.empty()) {
        auto n = frontier.front();
        frontier.pop();
        // cout << "visiting " << n << endl;
        for (auto e : adj[n]) {
            node_t to = to_node[e];
            if (level[to] != -1 || capacity[e] <= 0) continue;
            level[to] = level[n] + 1;
            frontier.push(to);
        }
    }
    return level[super_sink] != -1;
}

int dfs(node_t node, capacity_t minFlow) {
    if (node == super_sink) return minFlow;
    // cout << "visiting " << node << endl;
    dfs_depth++;
    for (auto edge : adj[node]) {
        if (capacity[edge] <= 0 || level[to_node[edge]] != level[node] + 1) {
            // cout << "node " << node << " a " << a << " b " << b << " edge " << edge 
            // << " capacity " << capacity[edge] << " level[a] " << level[a] << 
            // " level[b] " << level[b] << endl;
            // cout << "skip " << b << endl;
            continue;
        }
        int bottleneck = dfs(to_node[edge], min(minFlow, capacity[edge]));
        // cout << a << " -" << capacity[edge] << "> " << b << " bottleneck " << bottleneck << endl;
        if (bottleneck > 0) {
            capacity[edge] -= bottleneck;
            capacity[reverse_edge[edge]] += bottleneck;
            return bottleneck;
        }
    }
    level[node] = -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int nn = n * n;

    const node_t row_begin = nn;
    const node_t col_begin = row_begin + n;
    super_source = col_begin + n;
    super_sink = super_source + 1;
    nodes_size = super_sink + 1;

    for (int i = 0; i < nn; i++) {
        cin >> stones[i];
    }

    for (int node = 0; node < nn; node++) {
        if (stones[node] > 1) {
            add_edge(super_source, node, stones[node] - 1);
            add_edge(node, row_begin + node / n, stones[node] - 1);
            add_edge(node, col_begin + node % n, stones[node] - 1);
        } else if (stones[node] == 0) {
            add_edge(row_begin + node / n, node, 1);
            add_edge(col_begin + node % n, node, 1);
            add_edge(node, super_sink, 1);
        }
    }

    // max flow
    // cout << "max flow" << endl;
    int max_flow = 0;
    while (bfs()) {
        bfs_count++;
        // cout << "bfs finish" << endl;
        // for (int edge = 0; edge < edges.size(); edge++) {
        //     auto [a, b] = edges[edge];
        //     cout << a << "(" << level[a] << ") -" 
        //     << capacity[edge] << "> " << b << "(" << 
        //     level[b] << ")" << endl;
        // }
        // ranges::fill_n(nextEdge, nodes_size, 0);
        for (;;) {
            dfs_count++;
            // cout << "dfs" << endl;
            int bottleneck = dfs(super_source, capacity_t(-1));
            if (bottleneck <= 0) break;
            max_flow += bottleneck;
        }
    }
    cout << "dfs " << dfs_count << " bfs " << bfs_count << endl;
    cout << "dfs depth " << double(dfs_depth) / dfs_count << endl;

    int rest = 0;
    for (auto edge : adj[super_source]) {
        rest += capacity[edge];
    }
    // cout << max_flow << " + " << rest << " * 2" << endl;
    cout << max_flow + rest * 2 << endl;
}