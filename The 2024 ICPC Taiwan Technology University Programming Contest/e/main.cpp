#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Node {
	unsigned char alpha;
	Node* parent = nullptr;
	bool left_right = 0; // 0: left, 1: right
	Node* left = nullptr;
	Node* right = nullptr;
};

void print_postorder(Node* node) {
	if (node == nullptr) return;
	print_postorder(node->left);
	print_postorder(node->right);
	cout << node->alpha;
}


void print_right(Node* node, int depth, string& s) {
	if (node == nullptr) return;
	if (depth >= s.size()) {
		s += node->alpha;
	} else {
		s[depth] = node->alpha;
	}
	print_right(node->left, depth + 1, s);
	print_right(node->right, depth + 1, s);
}

void print_right_view(Node* node) {
	string s;
	print_right(node, 0, s);
	cout << s;
}


int main() {
	int T; cin >> T;
	for (int _ = 0; _ < T; _++) {
		string inorder; cin >> inorder;
		string preorder; cin >> preorder;
		map<unsigned char, size_t> char2nodeId;
		vector<Node> nodes; // same order with inorder
		nodes.resize(preorder.size());
		for (int i = 0; i < inorder.size(); i++) {
			nodes[i].alpha = inorder[i];
			char2nodeId[inorder[i]] = i;
		}
		
		for (int i = 0; i < preorder.size(); i++) {
			size_t nodeId = char2nodeId[preorder[i]];
			Node* node = &nodes[nodeId];
			if (node->parent) {
				if (node->left_right) {
					node->parent->right = node;
				} else {
					node->parent->left = node;
				}
			}
			for (size_t id = nodeId; ;) {
				if (id == 0) break;
				id--;
				if (nodes[id].parent != node->parent) break;
				//if (nodes[id].left_right != node->left_right) break;
				nodes[id].parent = node;
				nodes[id].left_right = 0; // left
			}
			for (size_t id = nodeId + 1; ; id++) {
				if (id >= nodes.size()) break;
				if (nodes[id].parent != node->parent) break;
				//if (nodes[id].left_right != node->left_right) break;
				nodes[id].parent = node;
				nodes[id].left_right = 1; // right
			}
		}
		
		Node* root = &nodes[char2nodeId[preorder[0]]];
		print_postorder(root);
		cout << " ";
		print_right_view(root);
		
		
		cout << endl;
	}

	return 0;
}

