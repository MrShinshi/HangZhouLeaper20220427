#ifdef DEBUG

#include <iostream>
#include <list>
#include <vector>

using std::list;
using std::vector;

struct Node
{
	int nId;  // �ڵ��ID��ÿ���ڵ��һ�޶����ұش���0
	int nPre1;  // �ڵ�������������1ǰ��ڵ㣬���˽ڵ�û�и����͵�ǰ��ڵ㣬��Ϊ-1
	int nPre2;  // �ڵ�������������2ǰ��ڵ㣬���˽ڵ�û�и����͵�ǰ��ڵ㣬��Ϊ-1

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
	/* ��1 */
	Nodes nodes1;
	nodes1.AddNode(Node(1, -1, -1));
	nodes1.AddNode(Node(2, 1, -1));
	nodes1.AddNode(Node(3, 1, 2));

	list<int> listId1 = nodes1.Solution();

	/* ��2 */
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