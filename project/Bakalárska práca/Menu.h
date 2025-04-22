#pragma once
#include "Data.h"
#include "Tree.h"
#include <vector>
class Menu
{
private:
	Data* data = nullptr;
	Tree* tree = nullptr;

public:
	Menu();
	void spustiProgram();
	~Menu();
	std::vector<int> loadIndexs();
};

