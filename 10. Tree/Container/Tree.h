#pragma once

#include "Node.h"
#include <vector>
#include <iostream>

template<typename T>
class Tree
{
public:
	Tree(const T& data)
	{
		root = new Node<T>(data);
	}

	~Tree()
	{
		// Todo : 자손 노드 모두 제거하는 함수 구현 후 호출.
	}

public:

	// 부모 노드의 값을 사용해 해당 부모에 자손을 추가.
	bool AddChild(const T& parentData, const T& childData)
	{
		// 부모 노드 검색.
		// 검색 함수 구현 후 호출.
		Node<T>* outParent = nullptr;
		bool result = FindRecursive(parentData, root, outParent);

		// 부모 검색에 성공했으면 자손 노드 추가.
		if (result)
		{
			outParent->AddChild(childData);
			return true;
		}

		return false;
	}

	// 검색 함수
	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

private:

	// data : 검색하려는 값.
	// node : 현재 검색하는 노드
	// outNode : 검색에 성공했을 때 반환할 노드.
	// 함수의 반환 값 : 검색 성공 실패 여부.
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		// 검색 실패(탈출 조건).
		if (node == nullptr)
		{
			outNode = nullptr;
			return false;
		}

		// 노드가 가진 값이 검색하는 값인지 비교.
		// 검색 성공.
		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		// 자손 노드로 내려가면서 재귀적으로 추가 검색 진행.
		std::vector<Node<T>*>& children = node->GetChildren();
		const int length = static_cast<int>(children.size());
		for (int i = 0; i < length; i++)
		{
			// 자손 노드 검색 진행.
			bool result = FindRecursive(data, children[i], outNode);
			if (result)
			{
				return true;
			}
		}

		outNode = nullptr;
		return false;
	}


private:
	Node<T>* root = nullptr;
};
