#include "Container/Queue.h"

int main()
{
	Queue<int> queue;

	const int count = 10;
	for (int i = 0; i < count; i++)
	{
		queue.Enqueue(i + 1);
	}

	queue.Print();

	std::cin.get();
}