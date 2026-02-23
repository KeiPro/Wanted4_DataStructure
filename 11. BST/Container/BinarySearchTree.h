#pragma once

#include "Node.h"

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{

	}

	~BinarySearchTree()
	{
		Destroy();
	}
		
	// 삽입.
	// Rule
	// 0. 중복된 값 허용 안함.
	// 1. 루트 노드 부터 비교 시작.
	// 1-1. 루트가 null이면 루트 생성.
	// 2. 추가할 값이 작으면 왼쪽에 저장.
	// 3. 추가할 값이 크면 오른쪽에 저장.
	bool InsertNode(const T& newData)
	{
		// 중복 여부 확인
		Node<T>* outNode = nullptr;
		if (SearchNode(newData, outNode))
		{
			// 중복된 값이 있으면 삽입 실패.
			return false;
		}

		// 루트가 없으면 루트 노드 생성.
		if (root == nullptr)
		{
			root = new Node<T>(newData);
			return true;
		}

		// Todo : 2/3을 처리하기 위해 재귀 함수 호출.
		root = InsertNodeRecursive(
			root, nullptr, newData
		);

		return true;
	}

	// 삭제.
	bool DeleteNode(const T& deleteData)
	{
		DeleteNodeRecursive(root, deleteData, root);
	}


	// 검색.
	bool SearchNode(const T& data, Node<T>*& outNode)
	{
		return SearchNodeRecursive(root, data, outNode);
	}

	// 순회

private:
	// 재귀 함수.

	// 검색 재귀 함수.
	bool SearchNodeRecursive(Node<T>* node, const T& data, Node<T>*& outNode)
	{
		// 검색 실패.
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// 찾았는지 확인.
		if (node->data == data)
		{
			outNode = node;
			return true;
		}

		// 작은 경우 왼쪽으로 내려감
		if (node->data > data)
		{
			return SearchNodeRecursive(node->left, data, outNode);
		}
		else
		{
			return SearchNodeRecursive(node->right, data, outNode);
		}
	}

	// 삽입 재귀 함수.
	Node<T>* InsertNodeRecursive(Node<T>* node, Node<T>* parent, const T& newData)
	{
		if (node == nullptr)
		{
			return new Node<T>(newData, parent);
		}

		// 추가하려는 값이 비교 노드 보다 작으면
		// 왼쪽 하위 트리로 탐색 진행.
		if (node->data > newData)
		{
			node->left = InsertNodeRecursive(node->left, node, newData);
		}
		else
		{
			node->right = InsertNodeRecursive(node->right, node, newData);
		}

		return node;
	}

	// 삭제 재귀 함수
	bool DeleteNodeRecursive(Node<T>* node, const T& deleteData, Node<T>*& outNode)
	{
		// 노드가 null인 경우는 삭제할 노드를 찾지 못한 경우.
		// 삭제 실패.
		 
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// 비교 값이 작은 경우 왼쪽으로.
		if (node->data > deleteData)
		{
			return DeleteNodeRecursive(node->left, deleteData, node->left);
		}
		

		// 비교 값이 큰 경우 오른쪽으로.
		else if (node->data < deleteData)
		{
			return DeleteNodeRecursive(node->right, deleteData, node->right);
		}

		else
		{
			// 경우의 수 - 자식이 없는 경우.
			// (left, right 모두 null)
			if (!node->left && !node->right)
			{
				delete node;
				outNode = nullptr;
				return true;
			}

			// 경우의 수 2 - 자식 노드 둘 다 있는 경우.
			if (node->left && node->right)
			{
				// 왼쪽 하위 노드 중에서 가장 큰 값.

				// 오른쪽 하위 노드 중에서 가장 작은 값.

				// Todo : 부분 함수 구현.
				// 하위 노드에서 최소값 찾는 함수 구현.
				node->data = SearchMinValue(node->right)->data;

				// 오른쪽 하위 트리에서 가장 작은 값의 노드를 삭제 및 정리.
				DeleteNodeRecursive(node->right, node->data, node);

				return true;
			}

			// 경우의 수 3 - 둘 중에 하나만 있는 경우.
			else
			{
				//왼쪽 자손이 null -> 오른쪽 자손만 있는 경우.
				if (!node->left)
				{
					// 오른쪽 자손 정보를 임시 저장.
					Node<T>* right = node->right;

					// 오른쪽 자손의 부모를 삭제할 노드의 부모로 설정.
					right->parent = node->parent;

					// 노드 제거.
					delete node;

					outNode = right;
					return true;
				}
  				// 왼쪽 자손이 있는 경우
				else if (!node->right)
				{
					// 오른쪽 자손 정보를 임시 저장.
					Node<T>* left = node->left;

					// 오른쪽 자손의 부모를 삭제할 노드의 부모로 설정.
					left->parent = node->parent;

					// 노드 제거.
					delete node;

					outNode = left;
					return true;
				}
			}
		}

		// 오류
		outNode = nullptr;
		return false;
	}

	// 최소값 검색 함수.
	// node: 검색을 시작하는 노드
	Node<T>* SearchMinValue(Node<T>* node)
	{
		// 검색 시작.
		while (node->left)
		{
			// 왼쪽 하위 노드로 이동.
			node = node->left;
		}

		// 최소 값을 가진 노드 반환.
		return node;
	}

	// 파괴 함수.
	void Destroy()
	{
		if (!root)
			return;

		// 루트 노드부터 제거.
		DestroyRecursive(root);
	}

	void DestroyRecursive(Node<T>* node)
	{
		if (!node)
			return;

		if (!node->left && !node->right)
		{
			delete node;
			return;
		}

		// 왼쪽 하위 트리 삭제.
		DestroyRecursive(node->left);

		// 오른쪽 하위 트리 삭제.
		DestroyRecursive(node->right);

		// 노드 정리.
		delete node;
	}

private:

	// 루트 노드.
	Node<T>* root = nullptr;
};
