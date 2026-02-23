#pragma once

#include <iostream>

template<typename T>
class Node
{

	// friend 선언.
	template<typename T>
	friend class BinarySearchTree;

public:

	Node(const T& data, Node<T>* const parent = nullptr)
		: data(data), parent(parent)
	{
	}

private:

	T data = T();
	Node<T>* parent = nullptr;

	// 왼쪽 자손 노드.
	Node<T>* left = nullptr;

	// 오른쪽 자손 노드.
	Node<T>* right = nullptr;

};
