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
	std::string targetClassValue;
	std::string majorityClass;
public:
	Node() : isLeaf(false), splitAttribute(-1), splitThreshold(-1), majorityClass("") {};
	~Node();
	bool getLeaf() { return this->isLeaf; };
	void setLeaf(bool state) { this->isLeaf = state; };
	std::string getLabel() { return this->label; };
	void setLabel(std::string name) { this->label = name; };
	double getTreshold() { return this->splitThreshold; };
	void setTreshold(double splitThreshold) { this->splitThreshold = splitThreshold; };
	int getSplitAttribute() { return this->splitAttribute; };
	void setSplitAttribute(int value) { this->splitAttribute = value; };
	std::string getTargetClassValue() { return this->targetClassValue; };
	void setTargetClassValue(std::string value) { this->targetClassValue = value; };
	std::string getMajorityClass() { return this->majorityClass; };
	void setMajorityClass(std::string value) { this->majorityClass = value; };


	void addChild(Node* node);
	Node* getChild(int index) { return children[index]; };
	int getNumberOfChildren() { return children.size(); };
	void clearChildren() { this->children.clear(); };
};

