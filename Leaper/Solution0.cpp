//#define DEBUG
#ifdef DEBUG

#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <unordered_set>

template<typename T>
class Node
{
public:
	using Ptr = std::shared_ptr<Node>;
	using Wtr = std::weak_ptr<Node>;

	Node(T v, Node::Ptr nextPtr) : mValue(v), mNextPtr(nextPtr) {}

	void SetValue(T value) {
		mValue = value;
	}

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

template<typename T>
class NodeList {
public:
	using Ptr = std::shared_ptr<Node<T>>;
	using Wtr = std::weak_ptr<Node<T>>;
	using Set = std::unordered_set<Node<T>*>;
	using Vec = std::vector<Wtr>;
	NodeList() :head(nullptr) {}
	NodeList(T val) :head(new Node<T>(val)) {
		this->tail = this->head;
	}
	void Show();
	void Clear();
	bool Create(T val);//在链表末尾创建一个值为val的节点,并返回执行结果
	bool Create(Wtr addr, T val);//在指定节点后插入一个值为val的节点,并返回执行结果
	Vec Retrieve(T val);//在链表中查找所有值为val的节点,并返回其指针
	T Retrieve(Wtr addr);//返回地址为addr的节点的值
	bool Update(Wtr addr, T val);//修改地址为addr的节点的值为val,并返回执行结果
	bool Delete(Wtr addr);//删除地址为addr的节点,并返回执行结果
//private:
	Ptr head;
	Wtr tail;
	Set registry;
};

using std::list;
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
	std::cout << "Result 2 is " << std::boolalpha << bRet2 << std::endl;

	NodeList<int> list;
	list.Create(5);
	list.Create(6);
	list.Create(7);
	list.Create(8);
	list.Show();
	IntNode::Wtr ptr = list.head;

	try
	{
		for (IntNode::Wtr& ptr : list.Retrieve(8))
			list.Create(0);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	list.Clear();
	list.Show();
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

template<typename T>
void NodeList<T>::Show()
{
	std::cout << "-----------------------" << std::endl;
	Wtr ptr(head);
	while (ptr.lock()) {
		std::cout << (*ptr.lock()).GetValue() << std::endl;
		ptr = ptr.lock()->GetNext();
	}
}

template<typename T>
void NodeList<T>::Clear()
{
	head = nullptr;
	tail = head;
}

template<typename T>
bool NodeList<T>::Create(T val)
{
	try {
		if (head == nullptr) {
			head = Ptr(new Node<T>(val, nullptr));
			tail = head;
			std::cout << "申请head" << std::endl;
		}
		else {
			tail.lock()->SetNext(Ptr(new Node<T>(val, nullptr)));
			tail = tail.lock()->GetNext();
			std::cout << "申请node" << std::endl;
		}
	}
	catch (std::bad_alloc& e) {
		std::cout << "申请内存失败" << std::endl;
		std::cout << e.what() << std::endl;
		return false;
	}

	registry.insert(tail.lock().get());
	return true;
}

template<typename T>
bool NodeList<T>::Create(Wtr addr, T val)
{
	if (registry.find(addr.lock().get()) == registry.end())
		return false;
	
	try {
		Ptr ptr(addr.lock()->GetNext());//假设使用weak_point,则重组链表的过程中很容易因为步骤顺序导致链表错误被释放
		addr.lock()->SetNext(Ptr(new Node<T>(val, ptr)));
		registry.insert(addr.lock()->GetNext().get());
	}
	catch (std::bad_alloc& e) {
		std::cout << "申请内存失败" << std::endl;
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

template<typename T>
std::vector<std::weak_ptr<Node<T>>> NodeList<T>::Retrieve(T val)
{
	Vec list;
	Wtr ptr(head);
	while (ptr.lock()) {
		if (ptr.lock()->GetValue() == val)
			list.push_back(ptr);
		ptr = ptr.lock()->GetNext();
	}
	return list;
}

template<typename T>
T NodeList<T>::Retrieve(Wtr addr)//理论上只要这个地址是正确的直接访问也行,但建议用这个函数来访问确保安全性
{
	if (registry.find(addr.lock().get()) == registry.end())
		throw std::out_of_range("链表中不存在此节点");
	return addr.lock()->GetValue();
}

template<typename T>
bool NodeList<T>::Update(Wtr addr,T val)//同上
{
	if (registry.find(addr.lock().get()) == registry.end())
		throw std::out_of_range("链表中不存在此节点");
	addr.lock()->SetValue(val);
	return false;
}

template<typename T>
bool NodeList<T>::Delete(Wtr addr)
{
	auto it{ registry.find(addr.lock().get()) };

	if (it == registry.end())
		throw std::out_of_range("链表中不存在此节点");

	if (head.get() == addr.lock().get())
		head = head->GetNext();
	else if (tail.lock().get() == addr.lock().get()) {
		Wtr ptr{ head };
		while (ptr.lock()->GetNext().get() != tail.lock().get()) {
			ptr = ptr.lock()->GetNext();
		}
		ptr.lock()->SetNext(nullptr);
		tail = ptr;
	}
	else {
		it = registry.find(addr.lock()->GetNext().get());
		addr.lock()->SetValue(addr.lock()->GetNext()->GetValue());
		addr.lock()->SetNext(addr.lock()->GetNext()->GetNext());
	}

	registry.erase(it);
	return true;
}

#endif