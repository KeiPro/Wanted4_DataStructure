#include "Container/Tree.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Node<int>* parent = new Node<int>(10);
	//Node<int>* child = new Node<int>(5);
	//parent->AddChild(child);
	////child->SetParent(parent);

	//parent->RemoveChild(child);
	Tree<int> tree(10);
	tree.AddChild(10, 9);
	tree.AddChild(10, 8);
	tree.AddChild(9, 7);
	tree.AddChild(9, 6);

	Node<int>* outNode = nullptr;
	if (tree.Find(6, outNode))
	{
		
	}

	// 삭제 테스트.
	if (tree.Remove(9))
	{

	}

	// 전위 순회 테스트
	tree.PreorderTraversal();
}