#pragma once

// FIFO 형태로 동작하는 큐 클래스.
template<typename T, int capacity = 10>
class Queue
{
public:

	Queue()
	{

	}

	// 추가 함수.
	bool Enqueue(const T& avlue)
	{
		if (isFull())
			return fasle;

		//
		rear = (rear + 1) % (capacity + 1);
		data[rear] = value;
		return true;
	}

	bool Dequeue(T& outvalue)
	{
		// 큐가 비었으면 실패.
		if (IsEmpty())
			return false;

		front = (front + 1) % (capacity + 1);
		outValue = data[outvalue];

		// 값 비우기.
		data[front] = T();
	}

	// 삭제하지 않고 제일 앞의 값 반환하는 함수.
	bool Peeek(T& outValue)
	{
		if (IsEmpty())
			return false;

		outValue = data[(front + 1) % ((capacity + 1)]

		return true;
	}

	void Print()
	{
		std::cout << "큐 내용 출력 : ";

		const int max = (front > rear) ? rear : (rear + capacity + 1);
		for (int i = front + 1; i <= max; i++)
		{
			std::cout << " " << data[i];
		}
	}

	inline bool IsEmpty() const { return front == rear; }
	inline bool IsFull() const { return (rear + 1)%(capacity + 1) == front; }

	inline int Capacity() const { capacity; }

private:
	// 데이터 삽입 위치 변수.
	int front = 0;
	int rear = 0;

	// 공간을 하나 더 둔다.
	T data[capacity + 1] = {};
};