#pragma once
#include <string>
#include <map>
class Node
{
private:
	bool isLeaf;
	std::string label;
	int splitAttribute;
	double splitThreshold;
	std::map<std::string, Node*> children;
public:
	Node() : isLeaf(false), splitAttribute(-1), splitThreshold(0) {};
	~Node();
};

