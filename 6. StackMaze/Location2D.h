#pragma once

// 행렬 좌표를 관리하는 클래스.
class Location2D
{
public:
	Location2D(int row = 0, int col = 0)
		: row(row), col(col)
	{

	}

public:
	int row = 0;
	int col = 0;
};