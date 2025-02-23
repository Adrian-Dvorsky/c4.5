#include "Node.h"

Node::~Node()
{
}

void Node::addChild(Node* node)
{
	this->children.push_back(node);
}
