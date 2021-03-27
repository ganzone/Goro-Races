/*

File name: grNode.cpp

Description:
see grNode.h for a description about this class

*/


#include "stdafx.h"
#include "grnode.h"


BOOL const grNode::setId(CString nodeId)
{
	// Check if there is already a node in the three with same name
	if (find(nodeId) != NULL)
		return FALSE;

	// Set node name
	id = nodeId;

	return TRUE;
}


int const grNode::countSiblings(void)  const
{
	int siblings = 0;
	grNode *currentNode = nextNode;

	while (currentNode != this)
	{
        siblings++;
		currentNode = currentNode->nextNode;
	}

	return siblings;
}


int const grNode::countChildren(void) const
{
	if (childNode == NULL)
		return 0;
	else
		return 1 + childNode->countSiblings();
}


int const grNode::countNodes(void) const
{
	if (childNode == NULL)
		return 1;

	grNode *currentNode = childNode;
	int children = 1;
	
	do {
		children += 1 + currentNode->countNodes();
        currentNode = currentNode->nextNode;
	} while (currentNode != childNode);

	return children;
}


int const grNode::depth(void) const
{
	if (parentNode == NULL)
		return 0;
	else
		return 1 + parentNode->depth();
}

	
grNode *grNode::getRoot(void)
{
	if (parentNode == NULL)
		return this;
	else
		return parentNode->getRoot();
}


grNode *grNode::find(CString nodeId)
{
	grNode *foundNode;

	// Check if we are looking for this node
	if (id == nodeId)
		return this;

	// Search among children nodes
	if (hasChild())
		if (foundNode = childNode->find(nodeId))
			return foundNode;

	// Search among siblings nodes
	if (hasSiblings() && !isLastChild())
		if (foundNode = nextNode->find(nodeId))
			return foundNode;

	// Node not found
	return NULL;
}


BOOL const grNode::attach(grNode *newChild)
{
	ASSERT(newChild != NULL);

	// Check if newChild tree has already a node named as this
	if (getRoot()->find(newChild->id) != NULL)
		return FALSE;

	// Check if node is already attached and detach it
	if (newChild->hasParent())
		newChild->detach();

	// Attach the node
	if (childNode == NULL)
		childNode = newChild;
	else
	{
		childNode->prevNode->nextNode = newChild;
		newChild->prevNode = childNode->prevNode;
		childNode->prevNode = newChild;
		newChild->nextNode = childNode;
	}

	newChild->parentNode = this;

	return TRUE;
}


void grNode::detach(void)
{
	if (parentNode == NULL) // node is already detached: just return
		return;

	if (!hasSiblings())
		// node has no siblings: just update parent node
		parentNode->childNode = NULL;
	else
	{
		// node has siblings: update parent and siblings nodes
		if (isFirstChild())
			parentNode->childNode = nextNode;

		nextNode->prevNode = prevNode;
		prevNode->nextNode = nextNode;
	}
	
	// set this node as a stand-alone node
	parentNode = NULL;
	nextNode = this;
	prevNode = this;
}


grNode::grNode(void)
{
	id = "";
	parentNode = NULL;
	childNode = NULL;
	nextNode = this;
	prevNode = this;
}


grNode::~grNode(void)
{
	detach();

	while (childNode)
		delete childNode;
}