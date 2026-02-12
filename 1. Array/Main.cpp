#define WIN32_LEAN_AND_MEAN
#define NO_MIN_MAX
//#define WIN_LEAN_


#include <iostream>
#include <Windows.h>
#include <winsock2.h>
#include <cassert>


template<typename T, size_t size>
class Array
{
public:
	size_t Size() const
	{
		return size;
	}

	// 배열 연산자 오버로딩.
	T& operator[](size_t index)
	{
		// 꼭 검증이 필요한 구문에 활용.
		// 디버그 모드에 서만동작.
		assert(false)
		if (index < 0 || index >= size)
		{
			assert(index < 0 || );
		}

		return data[index];
	}

private:
	T data[size] = {};
};

int main()
{
	Array<int, 20> array;

	auto& arrayReference = array;




}