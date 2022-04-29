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

typedef list<int> List;
typedef unordered_map<int, std::pair<int, int>> Dict;

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

void Show(list<int>& list) {
	for (int& n : list)
		std::cout << n << ' ';
	std::cout << std::endl;
}

int main()
{
	/* ��1 */
	Nodes nodes1;
	//nodes1.AddNode(Node(1, -1, -1));
	//nodes1.AddNode(Node(2, 1, -1));
	//nodes1.AddNode(Node(3, 2, 1));
	//nodes1.AddNode(Node(4, 2, 5));
	//nodes1.AddNode(Node(5, 2, 1));

	//���������е����ݹ���ì��,ִ��Solutionʱ��������������󷵻�
	//ԭ������Ǳ�ջ,������Ҫ�߱��Ų�ì�ܵĹ���
	nodes1.AddNode(Node(6, 7, -1));
	nodes1.AddNode(Node(7, 6, -1));
	list<int> listId1 = nodes1.Solution(); 
	Show(listId1);


	/* ��2 */
	Nodes nodes2;
	nodes2.AddNode(Node(4, 13, -1));
	nodes2.AddNode(Node(5, -1, 4));
	nodes2.AddNode(Node(6, 7, -1));
	nodes2.AddNode(Node(7, 4, 5));
	nodes2.AddNode(Node(8, 5, 6));
	nodes2.AddNode(Node(10, -1, -1));
	nodes2.AddNode(Node(11, -1, -1));
	nodes2.AddNode(Node(12, -1, -1));
	nodes2.AddNode(Node(13, -1, -1));

	list<int> listId2 = nodes2.Solution();
	Show(listId2);
}

void AddList(List& list, Dict& dict, int code) {
	
	//���ù����ѵǼ�
	if (find(list.begin(), list.end(), code) != list.end())
		return;

	bool isFirstExists{ dict.find(dict[code].first) != dict.end() };
	bool isSecondExists{ dict.find(dict[code].second) != dict.end() };

	//���ù��򲻴�������,ֱ�Ӽ���list
	if (isFirstExists == false && isSecondExists == false) {
		list.push_front(code);
		return;
	}

	//������first����,�ǼǸ�����
	if (isFirstExists) {
		if (find(list.begin(), list.end(), dict[code].first) == list.end()) {
			AddList(list, dict, dict[code].first);
		}
	}

	//������second����,�ǼǸ�����
	if (isSecondExists) {
		if (find(list.begin(), list.end(), dict[code].second) == list.end()) {
			AddList(list, dict, dict[code].second);
		}
	}

	list.push_back(code);

	return;
}

//�ݹ�˼·:
//	����ù����Ѵ�����list��,��return									finish
//	����ù����������󶼲���dict��,��ֱ��list.push_front��return		finish
//	����ù���ĳ��������dict�е�����list��,�����������list			finish
list<int> Nodes::Solution()
{
	List list;
	Dict dict;

	//�������ż���������ֵ�
	for (const auto& node : this->mNodes)
		dict.emplace(node.nId, std::make_pair(node.nPre1, node.nPre2));

	//��������
	for(const auto& node : this->mNodes)
		AddList(list, dict, node.nId);

	return list;
}

#endif