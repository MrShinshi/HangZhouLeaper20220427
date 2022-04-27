/*! 感谢您参与利珀科技笔试，题目说明如下：
* [Q0]
* 给定指向某个链表头结点的智能指针，其节点的定义如 模板类Node 所示
* 请设计一个算法函数 Solution，用于检查此链表中是否存在环状结构。
* 注意：可以根据需要，为 Node 添加合适的成员或方法
*
* [Q0 附加] 完成后可跳过 Q1 ~ 3
* 设计一个 NodeList 类，用于 Node 链表的 CRUD，并在修改链表时查环。
* 注意：不要重复对未修改的链表段进行检查。
*/
#ifdef DEBUG

#include <iostream>
#include <memory>

template<typename T>
class Node
{
    /**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**/
    /* 若有必要，请在此为模板类添加合适的成员或方法 */
    /**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!**/

public:
	using Ptr = std::shared_ptr<Node>;
	Node(T v, Node::Ptr nextPtr)
		: mValue(v), mNextPtr(nextPtr)
	{}

	T GetValue() const { return mValue; }
	void SetNext(Node::Ptr nextPtr) { mNextPtr = nextPtr; }

	static Node::Ptr MakeNode(T v, Node::Ptr nextPtr) {
		return std::make_shared<Node>(v, nextPtr);
	}

private:
	T mValue; // 节点的值
	Node::Ptr mNextPtr; // 节点的下一个节点
};

using IntNode = Node<int>;

bool Solution(IntNode::Ptr headPtr);

int main()
{
	std::cout << "Hello World!\n";

	/* 例1 */
	IntNode::Ptr node5 = IntNode::MakeNode(5, nullptr); // 5
	IntNode::Ptr node4 = IntNode::MakeNode(4, node5); // 4->5
	IntNode::Ptr node3 = IntNode::MakeNode(3, node4); // 3->4
	IntNode::Ptr node2 = IntNode::MakeNode(2, node3); // 2->3
	IntNode::Ptr node1 = IntNode::MakeNode(1, node2); // 1->2
	bool bRet1 = Solution(node1);  // 传入链表头节点node1的地址
	std::cout << "Result 1 is " << bRet1;
	// bRet1结果应该为false
	/* 解释：链表完整为 1->2->3->4->5，其中不存在环状结构，故返回false */

	/* 例2 */
	IntNode::Ptr node9 = IntNode::MakeNode(9, nullptr); // 9
	IntNode::Ptr node8 = IntNode::MakeNode(8, node9); // 8->9
	IntNode::Ptr node7 = IntNode::MakeNode(7, node8); // 7->8
	IntNode::Ptr node6 = IntNode::MakeNode(6, node7); // 6->7
	node9->SetNext(node7);  // 9->7
	bool bRet2 = Solution(node6);  // 传入链表头节点node6的地址
	std::cout << "Result 2 is " << bRet2;
	// bRet2结果应该为true
	/* 解释：链表完整为 6->7->8->9->7->8->9->...，其中789节点存在环状结构，故返回true */
	
	/* 例3 */
	// 若链表长度为 100000，环较小（如3个节点的环）且可能存在于链表前、中、尾部
	// 如何设计解决方案，使得计算量最小
}

/*! 检查输入的此链表中是否存在环状结构
* @param headPtr 链表头节点对应的智能指针
* @retval 若存在环，返回true；否则，返回false
*/
bool Solution(IntNode::Ptr headPtr)
{
	/**!!!!!!!!!!!!!!!!!!!!!!!!**/
	/* 请在此函数中写下你的解法 */
	/**!!!!!!!!!!!!!!!!!!!!!!!!**/
	return false;
}

#endif