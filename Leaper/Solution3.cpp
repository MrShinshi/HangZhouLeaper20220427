#define DEBUG
#ifdef DEBUG

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::list;
using std::vector;
using std::unordered_map;

struct Node
{
	int nId;
	int nPre1;
	int nPre2;

	Node(int id, int pre1, int pre2) : nId(id), nPre1(pre1), nPre2(pre2) {}
};

class Nodes
{
public:
	Nodes() {}

	void AddNode(const Node& node) {
		mNodes.push_back(node);
	}

	list<int> Solution();

private:
	vector<Node> mNodes;
};

int main()
{
	/* Àý1 */
	Nodes nodes1;
	nodes1.AddNode(Node(1, -1, -1));
	nodes1.AddNode(Node(2, 1, -1));
	nodes1.AddNode(Node(3, 1, 2));

	list<int> listId1 = nodes1.Solution();

	/* Àý2 */
	Nodes nodes2;
	nodes2.AddNode(Node(4, 1, -1));
	nodes2.AddNode(Node(5, -1, 4));
	nodes2.AddNode(Node(6, -1, -1));

	list<int> listId2 = nodes2.Solution();
}

list<int> Nodes::Solution()
{
	unordered_map<int, std::pair<int, int>> dict;
	list<int> res;
	int size = this->mNodes.size();
	for (int i{}; i < size; i++) {
		dict.emplace(this->mNodes[i].nId, std::make_pair(this->mNodes[i].nPre1, this->mNodes[i].nPre2));
		res.push_back(this->mNodes[i].nId);
	}
	for (auto& pair : dict) {
		std::cout << pair.second.first << pair.second.second << std::endl;
	}

	

	return list<int>();
}

#endif