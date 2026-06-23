#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct NeighborNode;

struct Node {
    size_t id;
    list<NeighborNode> neighbors;
};

struct NeighborNode {
    int weight;
    Node* node;
};

int main() {
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int nodes_count; cin >> nodes_count;
        vector<Node> nodes{nodes_count};
        for (int i = 0; i < nodes_count; i++) nodes[i].id = i;
        // cout << nodes.size() << endl;
        for (int _ = 0; _ < nodes_count; _++) {
            int src; cin >> src;
            int des; cin >> des;
            int w; cin >> w;
            // cout << src << " -" << w << "> " << des << endl;
            NeighborNode neighbor{.weight = w, .node = &nodes[des]};
            nodes[src].neighbors.push_back(neighbor);
        }

        vector<int> incoming_count;
        incoming_count.resize(nodes_count);
        for (int i = 0; i < nodes_count; i++) incoming_count[i] = 0;
        for (auto& node : nodes) {
            for (auto& neighbor : node.neighbors) {
                incoming_count[neighbor.node->id]++;
            }
        }

        vector<Node*> topological_orderd_nodes;
        auto tmp_incoming_count = incoming_count;
        list<size_t> remaining_node_ids;
        remaining_node_ids.resize(nodes_count);
        int counter = 0; for (auto& id : remaining_node_ids) id = counter++;
        while (!remaining_node_ids.empty()) {
            auto min_incoming_node_id = min_element(
                remaining_node_ids.begin(), 
                remaining_node_ids.end(), 
                [&](size_t a, size_t b){
                    return tmp_incoming_count[a] < tmp_incoming_count[b];
                }
            );
            auto& node = nodes[*min_incoming_node_id];
            topological_orderd_nodes.push_back(&node);
            for (auto& neighbor : node.neighbors) {
                tmp_incoming_count[neighbor.node->id]--;
            }
            remaining_node_ids.erase(min_incoming_node_id);
        }

        vector<int> max_weights; // in original order
        max_weights.resize(nodes_count);
        for (auto& w : max_weights) w = -99999999;
        max_weights[topological_orderd_nodes[0]->id] = 0;
        for (auto node : topological_orderd_nodes) {
            for (auto neighbor : node->neighbors) {
                auto new_weight = max_weights[node->id] + neighbor.weight;
                if (new_weight > max_weights[neighbor.node->id]) {
                    max_weights[neighbor.node->id] = new_weight;
                }
            }

            // for (auto node : topological_orderd_nodes) {
            //     cout << max_weights[node->id] << " ";
            // }
            // cout << endl;
        }
        // cout << endl;

        cout << *max_element(max_weights.begin(), max_weights.end()) << endl;

        // for (auto& ptr_node : topological_orderd_nodes) {
        //     auto node = *ptr_node;
        //     cout << node.id;
        //     for (auto& neighbor : node.neighbors) {
        //         cout << " -" << neighbor.weight << "> " << neighbor.node->id;
        //     }
        //     cout << endl;
        // }
    }

    return 0;
}