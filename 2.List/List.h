#pragma once

#include <iostream>
#include <cassert>

template<typename List>
class ListIterator
{
public:

	// 타입 알리아싱 지정.
	// List가 템플릿 파라미터로 넘어오는 경우 typename 까지 지정.
	using ValueType = typename List::ValueType; //  typename List:: 을 함으로써, 템플릿에서 넘어온다는 것을 의미함.
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	ListIterator(PointerType ptr)
		: ptr(ptr)
	{
	}

	// 연산자 오버로딩.

	// 전위 증가 연산자.
	ListIterator& operator++()
	{
		++ptr;
		return *this;
	}

	// 후위 증가 연산자.
	ListIterator& operator++(int)
	{
		// 현재 반복자를 임시 저장.
		ListIterator iterator = *this;

		// 내부 포인터 ++ 처리.
		++(*this);

		// 앞서 저장했던 반복자 반환.
		return iterator;
	}

	// 전위 감소 연산자.
	ListIterator& operator--()
	{
		--ptr;
		return *this;
	}

	// 후위 감소 연산자.
	ListIterator& operator--(int)
	{
		// 현재 반복자를 임시 저장.
		ListIterator iterator = *this;

		// 내부 포인터 -- 처리.
		--(*this);

		// 앞서 저장했던 반복자 반환.
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(ptr + index);
	}

	PointerType operator->()
	{
		return ptr;
	}

	ReferenceType operator*()
	{
		return *ptr;
	}

	// 비교 연산자 오버로딩
	bool operator==(const ListIterator& other) const
	{
		return ptr = other.ptr;
	}

	// 비교 연산자 오버로딩
	bool operator!=(const ListIterator& other) const
	{
		return !(*this == other);
	}

private:
	// 반복자는 결국 포인터.
	PointerType ptr = nullptr;

};

//// 반복자.
//template<typename List>
//class ListIterator
//{
//public:
//	// 타입 알리아싱 지정.
//	// List가 템플릿 파라미터로 넘어오는 경우 typename 까지 지정.
//	using ValueType = typename List::ValueType;
//	using PointerType = ValueType*;
//	using ReferenceType = ValueType&;
//
//public:
//	ListIterator(PointerType ptr)
//		: ptr(ptr)
//	{
//	}
//
//	// 연산자 오버로딩.
//
//	// 전위 증가 연산자.
//	ListIterator& operator++()
//	{
//		++ptr;
//		return *this;
//	}
//
//	// 후위 증가 연산자.
//	ListIterator& operator++(int)
//	{
//		// 현재 반복자를 임시 저장.
//		ListIterator iterator = *this;
//
//		// 내부 포인터 ++ 처리.
//		++(*this);
//
//		// 앞서 저장했던 반복자 반환.
//		return iterator;
//	}
//
//	// 전위 감소 연산자.
//	ListIterator& operator--()
//	{
//		--ptr;
//		return *this;
//	}
//
//	// 후위 감소 연산자.
//	ListIterator& operator--(int)
//	{
//		// 현재 반복자를 임시 저장.
//		ListIterator iterator = *this;
//
//		// 내부 포인터 -- 처리.
//		--(*this);
//
//		// 앞서 저장했던 반복자 반환.
//		return iterator;
//	}
//
//
//
//private:
//	// 반복자는 결국 포인터.
//	PointerType ptr = nullptr;
//};



template<typename T>
class List {

	// 타입 알리아싱 지정.
public:
	using ValueType = T;
	using Iterator = ListIterator<List<T>>;

public:
	List()
	{
		// Todo: 저장 공간 할당해야 함.
		Reallocate(capacity);
		//data = new T[capacity];
		//memset(data, 0, sizeof(T) * capacity);
	}

	~List()
	{
		// 자원 해제.
		if (data)
		{
			delete[] data;
		}
	}

public:
	// 저장 공간 할당(재할당)하는 함수.
	void Reallocate(int newCapacity)
	{
		// 1. 이주 할 새로운 공간 할당 (new).
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		if (newCapacity < size)
		{
			size = newCapacity;
		}

		// 2. 기존 항목을 새로운 공간에 복사/이동.
		/*for (int i = 0; i < size; i++)
		{
			newBlock[i] = data[i];
		}*/

		if (data)
		{
			memcpy(newBlock, data, sizeof(T) * size);
		}

		// 3. 기존 배열 공간 해제.
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

	void Add(const T& value)
	{
		// 가득찬 상태인지 확인.
		if (size == capacity)
		{
			// 크기 재할당.
			Reallocate(capacity * 2);
		}

		// 항목 추가.
		data[size] = value;
		++size;
	}

	void Add(T&& value)
	{
		// 가득찬 상태인지 확인.
		if (size == capacity)
		{
			// 크기 재할당.
			Reallocate(capacity * 2);
		}

		// 값 저장 시 이동 처리.
		data[size] = std::move(value);
		++size;
	}

	// 인덱스 연산자 오버로딩
	T& operator[](int index)
	{
		// index범위 확인.
		assert(index < 0 || index >= size);

		return data[index];
	}


	int Size() const { return size; }
	int Capacity() const { return capacity; }

	// 범위 기반 루프 처리를 위한 함수 작성(begin/end).
	// 배열의 첫 위치를 반환하는 함수.
	T* begin()
	{
		//return Iterator(data);
		return data;
	}

	// 배열에 저장된 마지막 요소
	T* end()
	{
		//return Iterator(data + size);
		return data + size;
	}

private:
	// 힙에 할당되는 배열을 관리할 포인터 변수.
	T* data = nullptr;

	// 배열에 저장된 항목의 수
	int size = 0;

	// 배열 저장 공간의 크기.
	int capacity = 2;
	

};