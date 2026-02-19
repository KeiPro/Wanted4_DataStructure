#include "Container/Stack.h"
#include <iostream>
#include <time.h>

int RandomRange(int min, int max)
{
	int diff = (max - min) + 1;
	return ((diff * rand()) / (RAND_MAX + 1)) + min;
}

float RandomRange(float min, float max)
{
	float percent = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	float diff = (max - min);
	return (percent * diff) + min;
}

int main()
{
	// random seed.
	srand(time(nullptr));

	// 스택 생성.
	const int count = 10;
	Stack<float, count> stack;

	for (int i = 0; i < count; i++)
		stack.Push(RandomRange(100.0f, 200.0f));

	// 스택에서 값 빼오면서 출력.
	const int stackCount = stack.Count();
	for (int i = 0; i < stackCount; i++)
	{
		float value = 0.0f;
		if (stack.Pop(value))
		{
			std::cout << value << "\n";
		}
	}

	std::cin.get();
}