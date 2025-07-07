#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Edge;

struct Node {
	int id;
	list<Edge*> out;
	list<Edge*> in;
};

struct Edge {
	int capacity;
	int flow = 0;
	Node* from;
	Node* to;
};

void print_graph(const vector<Node>& nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		cout << nodes[i].id;
		for (auto& edge : nodes[i].out) {
			cout << " -" << edge->flow << "/" << edge->capacity << "> " << edge->to->id;
		}
		for (auto& edge : nodes[i].in) {
			cout << " <" << edge->flow << "/" << edge->capacity << "- " << edge->from->id;
		}
		cout << endl;
	}
}

void print_edges(const vector<Edge>& edges) {
	for (auto& edge : edges) {
		cout << edge.from->id << " -" << edge.flow << "/" 
			<< edge.capacity << "> " << edge.to->id << endl;
	}
}

void print_route(const vector<Edge*>& route) {
	if (!route.size()) return;
	Node* node = route[0]->from;
	cout << node->id;
	for (Edge* edge : route) {
		if (node == edge->from) {
			cout << " -" << edge->flow << "/" << edge->capacity
				<< "> " << edge->to->id;
			node = edge->to;
		} else {
			cout << " <" << edge->flow << "/" << edge->capacity
				<< "- " << edge->from->id;
			node = edge->from;
		}
	}
}

bool DFS(
	Node* node, vector<Node>& nodes, 
	vector<Edge*>& route, 
	set<Node*>&& visited = set<Node*>{}, 
	int depth = 0
) {
	if (visited.find(node) != visited.end()) {
		return false;
	}
	if (node->id == nodes.size() - 1) {
		route.resize(depth);
		return true;
	}
	visited.insert(node);
	for (Edge* edge : node->out) {
		if (edge->flow >= edge->capacity) continue;
		bool routeFound = DFS(edge->to, nodes, route, move(visited), depth + 1);
		if (routeFound) {
			route[depth] = edge;
			return true;
		}
	}
	for (Edge* edge : node->in) {
		if (edge->flow <= 0) continue;
		bool routeFound = DFS(edge->from, nodes, route, move(visited), depth + 1);
		if (routeFound) {
			route[depth] = edge;
			return true;
		}
	}
	
	return false;
}

int main() {
	int case_count; cin >> case_count;
	for (int _ = 0; _ < case_count; _++) {
		int edge_count; cin >> edge_count;
		vector<Edge> edges;
		edges.resize(edge_count);
		vector<Node> nodes;
		nodes.reserve(100);
		for (int i = 0; i < edge_count; i++) {
			int fromId, toId, capacity;
			cin >> fromId >> toId >> capacity;
			Edge& edge = edges[i];
			int maxId = max(fromId, toId);
			if (maxId >= nodes.size()) nodes.resize(maxId + 1);
			nodes[fromId].out.push_back(&edge);
			nodes[toId].in.push_back(&edge);
			edge.capacity = capacity;
			edge.from = &nodes[fromId];
			edge.to = &nodes[toId];
		}
		for (int i = 0; i < nodes.size(); i++) nodes[i].id = i;
		
		//set<Node*> visited;
		vector<Edge*> route;
		int maxFlow = 0;
		while (DFS(&nodes[0], nodes, route)) {
			int bottleneck = 99999999;
			Node* node = &nodes[0];
			for (Edge* edge : route) {
				if (node == edge->from) {
					if (edge->capacity - edge->flow < bottleneck) {
						bottleneck = edge->capacity - edge->flow;
					}
					node = edge->to;
				} else {
					if (edge->flow < bottleneck) {
						bottleneck = edge->flow;
					}
					node = edge->from;
				}
			}
			node = &nodes[0];
			for (Edge* edge : route) {
				if (node == edge->from) {
					edge->flow += bottleneck;
					node = edge->to;
				} else {
					edge->flow -= bottleneck;
					node = edge->from;
				}
			}
			maxFlow += bottleneck;
			
			// print_route(route); cout << endl;
			//print_graph(nodes);
		}
		
		cout << maxFlow << endl;
		//print_edges(edges);
		//print_graph(nodes);
	}

	return 0;
}