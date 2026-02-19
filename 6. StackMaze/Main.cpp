#include "Container/Stack.h"
#include "Location2D.h"
#include <iostream>
#include <Windows.h>

// Map (Maze).
// 작은 맵.
//const int MAZE_SIZE = 6;
//char map[MAZE_SIZE][MAZE_SIZE] =
//{
//	{'1','1','1','1','1','1'},
//	{'e','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','x'},
//	{'1','1','1','1','1','1'}
//};

// 큰 맵.
const int MAZE_SIZE = 20;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
	{'e', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'x'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
};

// 방문하려는 위치가 유효한지 확인하는 함수.
bool IsValidLocation(const Location2D& location)
{
	// 편의 목적
	const int row = location.row;
	const int col = location.col;

	// 인덱스 범위 확인.
	if (row < 0 || row >= MAZE_SIZE || col < 0 || col >= MAZE_SIZE)
		return false;

	// 이동하려는 곳이 이동 가능한지 확인.
	return map[row][col] == '0' || map[row][col] == 'x';
}

// 콘솔 화면 지우는 함수.
void ClearScreen()
{
	system("cls");
}

// 텍스트 색상 지정 함수.
void SetConsoleColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 맵 그리는 함수
void PrintMap(const Location2D& playerPosition, DWORD delay)
{
	// 쓰레드 재우는 함수.
	Sleep(delay);

	// 콘솔 화면 지우기.
	// ClearScreen();

	COORD coord;
	coord.X = 0;
	coord.Y = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	// 맵 순회하면서 그리기.
	for (int row = 0; row < MAZE_SIZE; row++)
	{
		for (int col = 0; col < MAZE_SIZE; col++)
		{
			if (row == playerPosition.row && col == playerPosition.col)
			{
				SetConsoleColor(FOREGROUND_GREEN);
				std::cout << "P ";

				SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				continue;
			}

			if (map[row][col] == 'x')
			{

				SetConsoleColor(FOREGROUND_RED);
				std::cout << "X ";
				SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				continue;
			}

			// 맵 출력.
			std::cout << map[row][col] << " ";
		}

		std::cout << "\n";
	}
}

int main()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// 시작 위치 검색.
	Location2D start;

	bool found = false;
	for (int row = 0; row < MAZE_SIZE; ++row)
	{
		for(int col = 0; col < MAZE_SIZE; ++col)
		{
			// 시작지점 문자 찾기.
			if (map[row][col] == 'e')
			{
				start.row = row;
				start.col = col;
				found = true;
				break;
			}
		}

		// 찾았으면 루프 종료.
		if (found)
			break;
	}

	PrintMap(start, 0);

	// 스택 생성.
	Stack<Location2D, MAZE_SIZE> stack;

	// 시작 위치 스택에 추가.
	stack.Push(start);

	// 길찾기 (DFS).
	while (!stack.IsEmpty())
	{
		// 방문할 위치 꺼내기.
		Location2D current;
		stack.Pop(current);

		// 위치 출력.
		PrintMap(current, 100);

		// 출구에 도착했는지 확인.
		if (map[current.row][current.col] == 'x')
		{
			std::cout << "\n 미로 탐색 성공\n";
			return 0;
		}

		// 방문 및 방문한 위치 표시.
		map[current.row][current.col] = '.';

		// 방문할 지점 스택에 추가.
		if (IsValidLocation(Location2D(current.row + 1, current.col)))
		{
			stack.Push(Location2D(current.row + 1, current.col));
		}

		if (IsValidLocation(Location2D(current.row - 1, current.col)))
		{
			stack.Push(Location2D(current.row - 1, current.col));
		}

		if (IsValidLocation(Location2D(current.row, current.col - 1)))
		{
			stack.Push(Location2D(current.row, current.col - 1));
		}

		if (IsValidLocation(Location2D(current.row, current.col + 1)))
		{
			stack.Push(Location2D(current.row, current.col + 1));
		}
	}

	// 길찾기 실패.
	std::cout << "미로 탐색 실패\n";
}