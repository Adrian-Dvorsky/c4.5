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
	std::string getLabel() { return this->label; };
	void setLabel(std::string name) { this->label = name; };
	double getTreshold() { return this->splitThreshold; };
	void setTreshold(double splitThreshold) { this->splitThreshold = splitThreshold; };
	int getSplitAttribute() { return this->splitAttribute; };
	void setSplitAttribute(int value) { this->splitAttribute = value; };

	void addChild(Node* node);

};

