#pragma once
#include "Data.h"
#include "Tree.h"
class Menu
{
private:
	Data* data = nullptr;
	Tree* tree = nullptr;

public:
	Menu();
	void spustiProgram();
	~Menu();
};

