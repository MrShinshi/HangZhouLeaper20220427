//#define DEBUG
#ifdef DEBUG

#include <iostream>
#include <memory>

template<typename T>
class Node
{
public:
	using Ptr = std::shared_ptr<Node>;
	using Wtr = std::weak_ptr<Node>;

	Node(T v, Node::Ptr nextPtr) : mValue(v), mNextPtr(nextPtr) {}

	T GetValue() const 
	{ 
		return mValue; 
	}

	void SetNext(Node::Ptr nextPtr) 
	{ 
		mNextPtr = nextPtr; 
	}

	Node::Ptr GetNext() 
	{
		return mNextPtr;
	}

	static Node::Ptr MakeNode(T v, Node::Ptr nextPtr) 
	{
		return std::make_shared<Node>(v, nextPtr);
	}

private:
	T mValue;
	Node::Ptr mNextPtr;
};

using IntNode = Node<int>;

bool Solution(IntNode::Ptr headPtr);

int main()
{
	IntNode::Ptr node5 = IntNode::MakeNode(5, nullptr);
	IntNode::Ptr node4 = IntNode::MakeNode(4, node5);
	IntNode::Ptr node3 = IntNode::MakeNode(3, node4);
	IntNode::Ptr node2 = IntNode::MakeNode(2, node3);
	IntNode::Ptr node1 = IntNode::MakeNode(1, node2);
	bool bRet1 = Solution(node1);
	std::cout << "Result 1 is " << std::boolalpha << bRet1 << std::endl;

	IntNode::Ptr node9 = IntNode::MakeNode(9, nullptr);
	IntNode::Ptr node8 = IntNode::MakeNode(8, node9);
	IntNode::Ptr node7 = IntNode::MakeNode(7, node8);
	IntNode::Ptr node6 = IntNode::MakeNode(6, node7);	
	node9->SetNext(node7);
	bool bRet2 = Solution(node6);
	std::cout << "Result 2 is " << std::boolalpha << bRet2;
}

bool Solution(IntNode::Ptr headPtr)
{
	//方案一: 遍历的同时使用哈希表记录节点的地址,若重复则返回 True,					空间复杂度 O(n), 时间复杂度 O(n)
	//方案二: 创建链表的同时记录链表节点数量, 若遍历链表步数大于节点数则返回 True,	空间复杂度 O(1), 时间复杂度 O(n)
	//方案三: 使用快慢指针, 若慢指针和快指针重叠则返回 True,						空间复杂度 O(1), 时间复杂度 O(n)

	//方案一: 时空复杂度太高,废除
	//方案二: 若一支长链表的开头有一个极小的循环, 步数将仍为链表节点数 k, 废除
	//方案三: 
	IntNode::Wtr slow(headPtr);
	IntNode::Wtr fast(headPtr);

	while (fast.lock() != nullptr) {
		slow = slow.lock()->GetNext();
		if (fast.lock()->GetNext() == nullptr)
			return false;
		fast = fast.lock()->GetNext()->GetNext();
		if (fast.lock() == slow.lock())
			return true;
	}

	return false;
}

#endif