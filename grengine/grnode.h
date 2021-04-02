/*

File name: grNode.h

Description:
grNode represents a single node of the cyclic linked list tree that grEngine
uses to mantain objects in the world. Each node has pointers to parent node,
first child node, next and previous sibling ("this" if node has no siblings).

*/


#ifndef _GRNODE_H
#define _GRNODE_H


class AFX_EXT_CLASS grNode
{
// Attributes
protected:
	CString id;							// The node identification name
public:
	grNode *parentNode;					// The parent node
	grNode *nextNode;					// The next sibling (this if no siblings)
	grNode *prevNode;					// The last sibling (this if no siblings)
	grNode *childNode;					// The first child node

// Functions
public:
	CString const &getId(void) const { return id; }		// Returns node ID
	BOOL const setId(CString nodeId);					// Set node ID

	inline BOOL const hasParent(void) const;	// Does the node have a parent ?
    inline BOOL const hasChild(void) const;		// Does the node have a child ?
	inline BOOL const hasSiblings(void) const;	// Does the node have any siblings ?
	inline BOOL const isFirstChild(void) const;	// Is the node the first child ?
	inline BOOL const isLastChild(void) const;	// Is the node the last child ?

	int const countSiblings(void) const;		// How many siblings has the node ?
	int const countChildren(void) const;		// How many children has the node ?
	int const countNodes(void) const;			// How many nodes are UNDER the node ?
	int const depth(void) const;				// Depth of the node
	grNode *getRoot(void);						// Returns the root of the tree
	grNode *find(CString nodeId);				// Returns the child/sibling node with
												// specified id or NULL	if not found

	// Attach node newChild to this node
	BOOL const attach(grNode *newChild);
	// Attach this node to newParent node
	BOOL const attachTo(grNode *newParent) { return newParent->attach(this); }
	// Detach this node from current parent
	void detach(void);

// Constructors and destructors
public:
	grNode(void);
	virtual ~grNode(void);
};


inline BOOL const grNode::hasParent(void) const
{
	if (parentNode != NULL)
		return TRUE;
	else
		return FALSE;
}


inline BOOL const grNode::hasChild(void) const
{
	if (childNode != NULL)
		return TRUE;
	else
		return FALSE;
}


inline BOOL const grNode::hasSiblings(void) const
{
	if (nextNode != this)
		return TRUE;
	else
		return FALSE;
}


inline BOOL const grNode::isFirstChild(void) const
{
	if (parentNode == NULL)
		return FALSE;

	if (parentNode->childNode == this)
		return TRUE;

	return FALSE;
}


inline BOOL const grNode::isLastChild(void) const
{
	if (parentNode == NULL)
		return FALSE;

	if (parentNode->childNode->prevNode == this)
		return TRUE;

	return FALSE;
}


#endif // _GRNODE_H