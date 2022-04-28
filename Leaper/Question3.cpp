#ifdef DEBUG

/*! 感谢您参与利珀科技笔试，题目说明如下：
* [Q3]
* 在机器视觉图像处理过程中，某些工序的进行需要依赖其他若干工序的执行结果，例如图像预处理、产品粗定位等。
* 换言之，在一个完整的周期中，若某工序a有前序的依赖工序bcd，则必须先进行被依赖的工序 bcd，然后才能执行工序 a。
* 我们现在使用结构体 Node 来模拟一个上述的工序，其定义代码如上，其中：
*   1. nId 是该工序的唯一标志符，是一个正整数，不同工序不会重复；
*   2. nPre1 表示该工序所依赖的第一种前道工序的ID，若不存在，则为-1；
*   3. nPre2 表示该工序所依赖的第二种前道工序的ID，若不存在，则为-1。
* 根据上述描述，设计一个算法函数 Solution，使其对给定的若干个 Node，可以得出一个合理的执行顺序，返回此顺序中各工序的ID。
* 注1：有可能存在 nPre1为-1 而 nPre2为正整数 的情况；也可能存在 nPre1/nPre2 既不是-1也不在给定的Node中的情况，
*      此情况下该前序节点视作已被执行过。
* 注2：节点的数量大概在1~1000个。
*/

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
	std::cout << "Hello World!\n";

	/* 例1 */
	Nodes nodes1;
	nodes1.AddNode(Node(1, -1, -1));
	nodes1.AddNode(Node(2, 1, -1));
	nodes1.AddNode(Node(3, 1, 2));

	list<int> listId1 = nodes1.Solution();
	// listId1 中结果应该为 list<int>{ 1, 2, 3 };
	/* 解释：1没有依赖项，2依赖于1，3依赖于1和2，因此方案应该按1->2->3的工序顺序执行 */


	/* 例2 */
	Nodes nodes2;
	nodes2.AddNode(Node(4, 1, -1));
	nodes2.AddNode(Node(5, -1, 4));
	nodes2.AddNode(Node(6, -1, -1));

	//原代码(疑似有误)list<int> listId2 = Solution(vecNode2);
	list<int> listId2 = nodes2.Solution();
	// listId2 中结果可以为以下任意一种 list<int>{ 6, 4, 5 }、list<int>{ 4, 6, 5 }、list<int>{ 4, 5, 6 };
	/* 解释：4依赖于1，但给定列表中没有1，视作1已被执行过，也即4没有依赖项；5依赖于4；6没有依赖项。
	 *       因此4应在5之前，6可以在任何位置，所以以上三种方案都可以使用 */
}

/*! 模拟执行工序
* @retval 返回合理的执行顺序
*/
list<int> Nodes::Solution()
{
	/**!!!!!!!!!!!!!!!!!!!!!!!!**/
	/* 请在此函数中写下你的解法 */
	/**!!!!!!!!!!!!!!!!!!!!!!!!**/
	return list<int>();
}

#endif