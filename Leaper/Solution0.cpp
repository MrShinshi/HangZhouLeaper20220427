#define DEBUG
#ifdef DEBUG

#include <iostream>
#include <memory>

template<typename T>
class Node
{
public:
	using Ptr = std::shared_ptr<Node>;

	Node(T v, Node::Ptr nextPtr) : mValue(v), mNextPtr(nextPtr) {}

	T GetValue() const { 
		return mValue; 
	}

	void SetNext(Node::Ptr nextPtr) { 
		mNextPtr = nextPtr; 
	}

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
	/* 例1 */
	IntNode::Ptr node5 = IntNode::MakeNode(5, nullptr); // 5
	IntNode::Ptr node4 = IntNode::MakeNode(4, node5); // 4->5
	IntNode::Ptr node3 = IntNode::MakeNode(3, node4); // 3->4
	IntNode::Ptr node2 = IntNode::MakeNode(2, node3); // 2->3
	IntNode::Ptr node1 = IntNode::MakeNode(1, node2); // 1->2
	bool bRet1 = Solution(node1);  // 传入链表头节点node1的地址
	std::cout << "Result 1 is " << bRet1 << std::endl;// bRet1结果应该为false

	/* 例2 */
	IntNode::Ptr node9 = IntNode::MakeNode(9, nullptr); // 9
	IntNode::Ptr node8 = IntNode::MakeNode(8, node9); // 8->9
	IntNode::Ptr node7 = IntNode::MakeNode(7, node8); // 7->8
	IntNode::Ptr node6 = IntNode::MakeNode(6, node7); // 6->7		
	node9->SetNext(node7);  // 9->7
	bool bRet2 = Solution(node6);  // 传入链表头节点node6的地址
	std::cout << "Result 2 is " << bRet2;// bRet2结果应该为true
}

bool Solution(IntNode::Ptr headPtr)
{
	//方案一: 遍历的同时使用哈希表记录节点的地址,若重复则返回 True,					空间复杂度 O(n),时间复杂度 O(n)
	//方案二: 创建链表的同时记录链表节点数量, 若遍历链表步数大于节点数则返回 True,	空间复杂度 O(1), 时间复杂度 O(n)
	//方案三: 使用快慢指针, 若慢指针和快指针重叠则返回 True,						空间复杂度 O(1), 时间复杂度 O(n)
	return false;
}

#endif // DEBUG