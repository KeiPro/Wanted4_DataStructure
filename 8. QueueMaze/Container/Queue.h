#pragma once

#include <iostream>

// FIFO ���·� �����ϴ� ť Ŭ����.
template<typename T, int capacity = 10>
class Queue
{
public:
	Queue()
	{
	}

	// �߰� �Լ�.
	bool Enqueue(const T& value)
	{
		// ť�� ������������ ����.
		if (IsFull())
		{
			return false;
		}

		// �߰� (�ε����� �迭 ������ ����� �ʵ���).
		rear = (rear + 1) % (capacity + 1);
		data[rear] = value;
		return true;
	}

	// ���� �Լ�.
	bool Dequeue(T& outValue)
	{
		// ť�� ������� ����.
		if (IsEmpty())
		{
			return false;
		}

		// �ε����� �迭 ���� ����� �ʵ���.
		front = (front + 1) % (capacity + 1);
		outValue = data[front];

		// �� ���� (�ʱ�ȭ).
		data[front] = T();
		//memset(&data[front], 0, sizeof(T));
		return true;
	}

	// �������� �ʰ� ���� ���� �� ��ȯ�ϴ� �Լ�.
	bool Peek(T& outValue)
	{
		// ť�� ������� ����.
		if (IsEmpty())
		{
			return false;
		}

		outValue = data[(front + 1) % (capacity + 1)];
		return true;
	}

	// ��� �Լ�.
	void Print()
	{
		std::cout << "ť ���� ���: ";

		// ���.
		const int max = (front < rear) ?
			rear : (rear + (capacity + 1));
		for (int ix = front + 1; ix <= max; ++ix)
		{
			std::cout << " " << data[ix % (capacity + 1)];
		}

		// ������.
		std::cout << "\n";
	}

	// Getter.
	inline bool IsEmpty() const { return rear == front; }
	inline bool IsFull() const
	{
		return ((rear + 1) % (capacity + 1)) == front;
	}
	inline int Capacity() const { return capacity; }

private:
	// ������ ���� ��ġ ����.
	int front = 0;

	// ������ ����(����) ��ġ ����.
	int rear = 0;

	// ������ ���� ����.
	T data[capacity + 1] = { };
};