#pragma once

template<typename T, int capacity = 10>
class Stack
{

public:
	// Constructor
	Stack()
		: top(0)
	{
	}

	// Add
	bool Push(const T& value)
	{
		if (IsFull())
			return false;

		data[top++] = value;
		return true;
	}

	// Remove
	bool Pop(T& outValue)
	{
		if (IsEmpty())
			return false;

		--top;
		outValue = data[top];
		return true;
	}

	// Getter.
	inline int Count() const { return top; }

	// check stack is empty.
	inline bool IsEmpty() const { return top == 0; }

	// check stack is full.
	inline bool IsFull() const { return top >= capacity; }

private:

	//clear stack.
	void Clear()
	{
		top = 0;
	}

private:
	// manage static array.
	T data[capacity] = {};

	// posiiton of the top element in the stack.
	int top = 0;
};