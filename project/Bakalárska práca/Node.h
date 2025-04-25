#pragma once
#include <string>
#include <map>
#include <vector>
class Node
{
private:
	bool isLeaf;
	std::string label;
	std::string nodeValue;
	int splitAttribute;
	double splitThreshold;
	std::vector<Node*> children;
	std::string targetClassValue;
	std::string majorityClass;
	int numSamples;
	double informationGain;
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
	std::string getNodeValue() { return this->nodeValue; };
	void setNodeValue(std::string value) { this->nodeValue = value; };

	void addChild(Node* node);
	Node* getChild(int index) { return children[index]; };
	int getNumberOfChildren() { return children.size(); };
	void removeChild(int index) {
		if (index < 0 || index >= children.size()) {
			return;
		}
		children.erase(children.begin() + index);
	}
	int getNumSamples() { return this->numSamples; };
	void setNumSamples(int value) { this->numSamples = value; };
	double getInformationGain() { return this->informationGain; };
	void setInformationGain(double value) { this->informationGain = value; };
	const std::vector<Node*> getChildren() { return this->children; };
};

