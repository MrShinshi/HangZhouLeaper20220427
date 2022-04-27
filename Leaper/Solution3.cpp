#ifdef DEBUG

#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::vector;

struct Node
{
	int nId;  // 节点的ID，每个节点独一无二，且必大于0
	int nPre1;  // 节点所依赖的类型1前序节点，若此节点没有该类型的前序节点，则为-1
	int nPre2;  // 节点所依赖的类型2前序节点，若此节点没有该类型的前序节点，则为-1

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
	/* 例1 */
	Nodes nodes1;
	nodes1.AddNode(Node(1, -1, -1));
	nodes1.AddNode(Node(2, 1, -1));
	nodes1.AddNode(Node(3, 1, 2));

	list<int> listId1 = nodes1.Solution();

	/* 例2 */
	Nodes nodes2;
	nodes2.AddNode(Node(4, 1, -1));
	nodes2.AddNode(Node(5, -1, 4));
	nodes2.AddNode(Node(6, -1, -1));

	list<int> listId2 = nodes2.Solution();
}

list<int> Nodes::Solution()
{
	
	return list<int>();
}

#endif // DEBUG