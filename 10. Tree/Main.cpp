#include "Container/Tree.h"

int main()
{
	Node<int>* parent = new Node<int>(10);
	Node<int>* child = new Node<int>(5);
	parent->AddChild(child);
	//child->SetParent(parent);

	parent->RemoveChild(child);
	/*Tree<int> tree(10);
	tree.AddChild(10, 9);
	tree.AddChild(10, 8);
	tree.AddChild(9, 7);
	tree.AddChild(9, 6);

	Node<int>* outNode = nullptr;
	if (tree.Find(6, outNode))
	{

	}*/
}