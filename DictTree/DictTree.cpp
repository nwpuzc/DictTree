#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

class TireNode {
private:
	TireNode* children[26];
	int count;
	char father;
	TireNode* fatherNode;
public:
	TireNode() {
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
		count = 0;
		father = '0';
		fatherNode = nullptr;
	}

	TireNode* get(char c) {
		if (children[c - 'a'] == nullptr) {
			children[c - 'a'] = new TireNode();
			children[c - 'a']->father = c;
			children[c - 'a']->fatherNode = this;
			count++;
		}

		return children[c - 'a'];
	}

	int getCount() {
		return count;
	}

	TireNode* getChildren(int i) {
		return children[i];
	}

	char getFather() {
		return father;
	}

	TireNode* getFatherNode() {
		return fatherNode;
	}
};

class Solution {
public:
	TireNode* createDictTree(vector<string> strings) {
		TireNode* root = new TireNode();
		for (string s : strings) {
			TireNode* tire = root;
			for (int i = 0; i < s.length(); i++) {
				tire = tire->get(s[i]);
			}
		}

		return root;
	}

	vector<char> depthTraversal2(TireNode* root) {
		vector<char> res;
		if (root == nullptr) {
			return res;
		}

		stack<TireNode*> stack;
		for (int i = 25; i >= 0; i--) {
			if (root->getChildren(i) != nullptr) {
				stack.push(root->getChildren(i));
			}
		}

		while (!stack.empty()) {
			TireNode* node = stack.top();
			stack.pop();

			res.push_back(node->getFather());

			if (node->getCount() == 0) {
				continue;
			}

			for (int i = 25; i >= 0; i--) {
				if (node->getChildren(i) != nullptr) {
					stack.push(node->getChildren(i));
				}
			}
		}

		return res;
	}

	void doDepthTrversal(TireNode* node, vector<char>& res) {
		if (node->getCount() == 0) {
			return;
		}

		for (int i = 0; i < 26; i++) {
			if (node->getChildren(i) != nullptr) {
				res.push_back('a' + i);
				doDepthTrversal(node->getChildren(i), res);
			}
		}
	}

	vector<char> depthTraversal(TireNode* root) {
		vector<char> res;
		if (root == nullptr) {
			return res;
		}

		doDepthTrversal(root, res);

		return res;
	}

	vector<char> widthTraversal(TireNode* root) {
		vector<char> res;
		if (root == nullptr) {
			return res;
		}

		queue<TireNode*> queue;

		for (int i = 0; i < 26; i++) {
			if (root->getChildren(i) != nullptr) {
				queue.push(root->getChildren(i));
				res.push_back('a' + i);
			}
		}

		while (!queue.empty()) {
			TireNode* node = queue.front();
			queue.pop();

			if (node->getCount() == 0) {
				continue;
			}

			for (int i = 0; i < 26; i++) {
				if (node->getChildren(i) != nullptr) {
					queue.push(node->getChildren(i));
					res.push_back('a' + i);
				}
			}
		}

		return res;
	}

	vector<string> getDict(TireNode* root) {
		vector<string> res;
		vector<TireNode*> leaf;
		queue<TireNode*> queue;

		for (int i = 0; i < 26; i++) {
			if (root->getChildren(i) == nullptr) {
				continue;
			}

			if (root->getChildren(i)->getCount() == 0) {
				leaf.push_back(root->getChildren(i));
			} else {
				queue.push(root->getChildren(i));
			}
		}

		while (!queue.empty()) {
			TireNode* node = queue.front();
			queue.pop();

			for (int i = 0; i < 26; i++) {
				if (node->getChildren(i) == nullptr) {
					continue;
				}

				if (node->getChildren(i)->getCount() == 0) {
					leaf.push_back(node->getChildren(i));
				} else {
					queue.push(node->getChildren(i));
				}
			}
		}

		for (int i = 0; i < leaf.size(); i++) {
			string temp = "";
			TireNode* node = leaf[i];

			while (node->getFatherNode() != nullptr) {
				temp += node->getFather();
				node = node->getFatherNode();
			}

			std::reverse(temp.begin(), temp.end());

			res.push_back(temp);
		}

		return res;
	}
};

template <class Anytype>
void printVector(vector<Anytype> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}

	cout << endl;
}

int main() {
	Solution s;
	vector<string> vec = { "china", "choose", "chip", "cup", "amb", "amq" };
	TireNode* root = s.createDictTree(vec);
	vector<char> widthRes = s.widthTraversal(root);

	printVector(widthRes);

	vector<char> depthRes = s.depthTraversal(root);
	printVector(depthRes);

	vector<char> depthRes2 = s.depthTraversal2(root);
	printVector(depthRes2);

	vector<string> dict = s.getDict(root);
	printVector(dict);

	//TODO: release memeory

	return 0;
}

