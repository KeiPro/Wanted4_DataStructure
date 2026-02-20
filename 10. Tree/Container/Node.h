#pragma once
#include <vector>

// 노드 삭제 편의 함수.
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

template<typename T>
class Node
{
public:
	Node() : data()
	{

	}

	Node(const T& data)
		: data(data)

	{

	}

	~Node()
	{
		data = T();
		parent = nullptr;
		children.clear();
	}

public:

	// 값을 전달해 자손 추가하는 함수.
	void AddChild(const T& data)
	{
		AddChild(new Node<T>(data));
	}

	// 노드를 직접 전달해 자손 추가하는 함수.
	void AddChild(Node<T>* newChild)
	{
		newChild->SetParent(this);

		// 자손 노드 목록에 새 노드 추가.
		children.emplace_back(newChild);
	}

	void RemoveChild(Node<T>* child)
	{
		// 하위노드까지 순회하면서 노드 검색 후 삭제.
		// 재귀 함수.
		RemoveChildRecursive(child);
	}

	// Getter/Setter.
	inline T GetData() { return data; }
	inline std::vector<Node<T>*>& GetChildren() { return children; }
	inline Node<T>* GetParent() { return parent; }
	inline void SetParent(Node<T>* newParent) { parent = newParent; }

private:

	// 노드 삭제 재귀 함수.
	// 언제 사용하는가? -> 자기 자신을 호출하면서 데이터의 범위가 줄어들 때.
	// 주의 사항! - 탈출 조건이 항상 있어야 함.
	// 주의 사항! - 스택 오버플로우 위험이 있음. 콜 스택을 사용하기 때문에 
	void RemoveChildRecursive(Node<T>* child)
	{
		// 탈출 조건.
		if (!child)
			return;

		// 하위 노드 확인.
		std::vector<Node<T>*>& children = child->GetChildren();

		// 경우의 수1 - 자손이 없는 경우.
		if (children.size() == 0)
		{
			auto& parentVector = child->GetParent()->GetChildren();
			auto childIt = std::find(parentVector.begin(), parentVector.end(), child);

			if (childIt != parentVector.end())
			{
				parentVector.erase(childIt);
			}

			SafeDelete(child);
			return;
		}

		// 경우의 수 2- 자손 노드가 있는 경우.
		while (children.size() > 0)
		{
			RemoveChildRecursive(children[0]);
		}

		auto& parentVector = child->GetParent()->GetChildren();
		auto childIt = std::find(parentVector.begin(), parentVector.end(), child);

		if (childIt != parentVector.end())
		{
			parentVector.erase(childIt);
		}

		SafeDelete(child);
	}


private:
	// 노드에 저장할 데이터.
	T data;

	// 부모 참조 노드.
	Node<T>* parent = nullptr;

	// 자손 노드 리스트(동적 배열)
	std::vector<Node<T>*> children;
};

