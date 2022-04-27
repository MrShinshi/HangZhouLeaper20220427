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
	std::cout << "Result 1 is " << bRet1 << std::endl;

	/* 例2 */
	IntNode::Ptr node9 = IntNode::MakeNode(9, nullptr); // 9
	IntNode::Ptr node8 = IntNode::MakeNode(8, node9); // 8->9
	IntNode::Ptr node7 = IntNode::MakeNode(7, node8); // 7->8
	IntNode::Ptr node6 = IntNode::MakeNode(6, node7); // 6->7		
	node9->SetNext(node7);  // 9->7
	bool bRet2 = Solution(node6);  // 传入链表头节点node6的地址
	std::cout << "Result 2 is " << bRet2;
}

bool Solution(IntNode::Ptr headPtr)
{

	return false;
}

#endif // DEBUG