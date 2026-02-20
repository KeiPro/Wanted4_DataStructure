#include "Container/HashTable.h"
#include <iostream>

int main()
{
	HashTable table;

	table.Add("Keipro", "010-1234-5555");
	table.Add("Keipro1", "010-1234-5555");
	table.Add("Keipro2", "010-1234-5555");
	table.Add("Keipro3", "010-1234-5555");
	table.Add("Keipro3", "010-1234-5555");
	table.Add("Keipro4", "010-1234-5555");
	table.Add("Keipro5", "010-1234-5555");
	table.Add("Keipro6", "010-1234-5555");
	table.Add("Keipro7", "010-1234-5555");
	table.Add("Keipro8", "010-1234-5555");

	table.Print();

	Pair<std::string, std::string> outValue;
	if (table.Find("Keipro5", outValue))
	{
		std::cout << "검색 성공. Key : " << outValue.key << " | Value : " << outValue.value << "\n";
	}

	table.Delete("Keipro3");
	table.Delete("Keipro4");
	table.Print();

	std::cin.get();
}