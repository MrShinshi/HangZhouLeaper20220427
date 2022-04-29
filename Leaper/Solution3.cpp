//#define DEBUG
#ifdef DEBUG

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::list;
using std::vector;
using std::unordered_map;

typedef struct Info;
typedef list<int> List;
typedef unordered_map<int, Info> Dict;

enum Status
{
	_NOT_USED,
	_CREATING,
	_CREATED
};

struct Info {
	int first{};
	int second{};
	int status{};
};

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

class TRASH {
public:
	TRASH(int& code):code(code) {

	}
	const int _getcode() const {
		return code;
	}
private:
	int code;
};

int main()
{
	/* 例1 */
	Nodes nodes1;

	//递归层数过高导致栈溢出
	//栈空间4MB时允许最大递归层数为736,扩容栈空间后才能达到1000
	for (int i{}; i < 736; i++)
		nodes1.AddNode(Node(i, i+1, -1));
	
	//下面两行的内容构成矛盾,执行Solution时导致爆栈,整个程序错误返回
	//nodes1.AddNode(Node(1, 2, -1));
	//nodes1.AddNode(Node(2, 1, -1));
	//代码需要具备排查矛盾的功能
	list<int> listId1 = nodes1.Solution(); 
	Show(listId1);


	/* 例2 */
	Nodes nodes2;


	nodes2.AddNode(Node(8, 7, -1));
	nodes2.AddNode(Node(9, 8, -1));
	nodes2.AddNode(Node(1, -1, -1));
	nodes2.AddNode(Node(2, 1, -1));
	nodes2.AddNode(Node(3, 2, -1));
	nodes2.AddNode(Node(6, 5, -1));
	nodes2.AddNode(Node(7, 6, -1));
	nodes2.AddNode(Node(4, 3, -1));
	nodes2.AddNode(Node(5, 4, -1));

	list<int> listId2 = nodes2.Solution();
	Show(listId2);
}

#define RECURRENCE

#ifdef RECURRENCE

//递归思路:
//	如果该工序已存在于list中,则return									finish
//	如果该工序两个需求都不在dict中,则直接list.push_front并return		finish
//	如果该工序某个需求在dict中但不在list中,则将需求工序加入list			finish
void AddList(List& list, Dict& dict, int code) {
	
	//若该工序已登记
	if (dict[code].status == _CREATED)
		return;

	if (dict[code].status == _CREATING) {
		throw TRASH(code);
		return;
	}

	dict[code].status = _CREATING;

	bool isFirstExists{ dict.find(dict[code].first) != dict.end() };
	bool isSecondExists{ dict.find(dict[code].second) != dict.end() };

	//若该工序不存在需求,直接加入list
	if (isFirstExists == false && isSecondExists == false) {
		list.push_front(code);
		dict[code].status = _CREATED;
		return;
	}

	try {
		//若需求first存在,登记该需求
		if (isFirstExists) {
			if (find(list.begin(), list.end(), dict[code].first) == list.end()) {
				AddList(list, dict, dict[code].first);
			}
		}

		//若需求second存在,登记该需求
		if (isSecondExists) {
			if (find(list.begin(), list.end(), dict[code].second) == list.end()) {
				AddList(list, dict, dict[code].second);
			}
		}
	}
	catch (TRASH& e) {
		std::cout << std::endl << std::endl << "\tSolution执行异常:" << std::endl << std::endl;
		std::cout << "\t\t工序 " << code << " - " << "工序 "<< e._getcode() << " 前置工序冲突" << std::endl << std::endl;
		exit(-1);
	}

	list.push_back(code);
	dict[code].status = _CREATED;

	return;
}

list<int> Nodes::Solution()
{
	List list;
	Dict dict;

	//将工序编号及需求加入字典
	for (const auto& node : this->mNodes)
		dict.emplace(node.nId, Info{ node.nPre1, node.nPre2, _NOT_USED });

	//构造链表
	for(const auto& node : this->mNodes)
		AddList(list, dict, node.nId);

	return list;
}

#endif // RECURRENCE

#ifdef ITERATION

list<int> Nodes::Solution() {

}

#endif // ITERATION

#endif // DEBUG