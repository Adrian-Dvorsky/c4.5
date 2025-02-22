#pragma once
#include <string>
#include <map>
#include <vector>
class Node
{
private:
	bool isLeaf;
	std::string label;
	int splitAttribute;
	double splitThreshold;
	std::vector<Node*> children;
public:
	Node() : isLeaf(false), splitAttribute(-1), splitThreshold(0) {};
	~Node();
	bool getLeaf() { return this->isLeaf;};
	void setLeaf(bool state) { this->isLeaf = state;};

};

