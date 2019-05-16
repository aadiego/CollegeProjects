#include "Stack.h"
#include "Card.h"

// *******************************************************************************************
// **     Function: Stack (constructor)														**
// **   Parameters:	N/A																		**
// **       Return:	N/A																		**
// **  Description: Initializes a new empty stack with the default values.					**
// *******************************************************************************************
template <class T>
Stack<T>::Stack() { }

// *******************************************************************************************
// **     Function: Stack (constructor)														**
// **   Parameters:	T data																	**
// **       Return:	N/A																		**
// **  Description: Initializes a new stack of the provided data type and creates the		**
// **				first linked list node object from the data parameter.					**
// *******************************************************************************************
template <class T>
Stack<T>::Stack(T data)
{
	push(data);
}

// *******************************************************************************************
// **     Function: Stack (constructor)														**
// **   Parameters:	const LinkedListNode& nodes	(by reference)								**
// **       Return:	N/A																		**
// **  Description: Initializes a new stack of the provided data type and creates the		**
// **				the stack using the provided linked list nodes.							**
// *******************************************************************************************
template <class T>
Stack<T>::Stack(LinkedListNode* nodes)
{
	// Set the stack lined list to the first element of the linked list nodes.
	stack = nodes;
}

// *******************************************************************************************
// **     Function: Stack (destructor)														**
// **   Parameters:	N/A																		**
// **       Return:	N/A																		**
// **  Description: Deletes the linked list nodes from the stack before destroying the		**
// **				object.																	**
// *******************************************************************************************
template <class T>
Stack<T>::~Stack()
{
	// Node traversal and next node pointers
	LinkedListNode* nodePtr;
	LinkedListNode* nextNode;

	// Set the node traversal pointer to the head node of the stack
	nodePtr = stack;

	// Loop through the stack deleting each node until no more nodes exist
	while (nodePtr != nullptr)
	{
		nextNode = nodePtr->nextNode;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

// *******************************************************************************************
// **     Function: push																	**
// **   Parameters:	T data																	**
// **       Return:	void																	**
// **  Description: Creates a new linked list node with the provided data and pushes the	**
// **				node to the top of the stack.											**
// *******************************************************************************************
template <class T>
void Stack<T>::push(T data)
{
	// Create the new LinkedListNode and set the values.
	LinkedListNode* newNode = new LinkedListNode;
	newNode->data = data;
	newNode->nextNode = nullptr;
	newNode->previousNode = nullptr;

	// Check if the stack has data. If not, set the new node to the head of the stack linked list and set the bottomNode pointer.
	if (!stack)
	{
		stack = newNode;
		bottomNode = newNode;
	}
	else
	{
		// Set the previousNode on the original head node to newNode, set newNode next node value to the head of the stack linked list,
		// and update the stack head to point to the new node.
		stack->previousNode = newNode;
		newNode->nextNode = stack;
		stack = newNode;
	}
	// Increment the stack size
	++stackSize;
}

// *******************************************************************************************
// **     Function: pop																		**
// **   Parameters:	N/A																		**
// **       Return:	void																	**
// **  Description: Deletes the top node of the stack.										**
// *******************************************************************************************
template <class T>
void Stack<T>::pop()
{
	// Pointers to hold the current head node and the second node.
	LinkedListNode* headNode = stack;
	LinkedListNode* nextNode = headNode->nextNode;

	// Update the head of the stack linked list to point to the second node, deletes the original head node, and sets the previousNode on the new
	// head node to nullptr.
	stack = nextNode;
	delete headNode;

	if (nextNode != nullptr)
	{
		stack->previousNode = nullptr;
	}

	// Decrement the stack size.
	--stackSize;
}

// *******************************************************************************************
// **     Function: pop_back																**
// **   Parameters:	N/A																		**
// **       Return:	void																	**
// **  Description: Deletes the bottom node of the stack.									**
// *******************************************************************************************
template <class T>
void Stack<T>::pop_back()
{
	// Pointer to hold the last node of the linked list.
	LinkedListNode* rearNode = bottomNode;

	// Set the bottomNode to the second to last node, deletes the original bottom node, and sets the nextNode on the new bottom node to nullptr.
	bottomNode = rearNode->previousNode;
	delete rearNode;
	bottomNode->nextNode = nullptr;

	// Decrement the stack size.
	--stackSize;
}


// *******************************************************************************************
// **     Function: top																		**
// **   Parameters:	N/A																		**
// **       Return:	T																		**
// **  Description: Returns the data from the top node of the stack.						**
// *******************************************************************************************
template <class T>
T Stack<T>::top()
{
	return stack->data;
}

// *******************************************************************************************
// **     Function: bottom																	**
// **   Parameters:	N/A																		**
// **       Return:	T																		**
// **  Description: Returns the data from the bottom node of the stack.						**
// *******************************************************************************************
template <class T>
T Stack<T>::bottom()
{
	return bottomNode->data;
}

// *******************************************************************************************
// **     Function: contains																**
// **   Parameters:	T search																**
// **       Return:	bool																	**
// **  Description: Returns true if the stack contains an object matching the search		**
// **				parameter.																**
// *******************************************************************************************
template <class T>
bool Stack<T>::contains(T search)
{
	// Node traversal pointer
	LinkedListNode* nodePtr;

	// Set the node traversal pointer to the head node of the stack
	nodePtr = stack;

	// Loop through the stack checking if the current node matches the search parameter value
	while (nodePtr != nullptr)
	{
		if (search.operator==(&nodePtr->data)) // figure out how to use c++ templates and the data type's == operator
		{
			return true;
		}
		nodePtr = nodePtr->nextNode;
	}
	return false;
}

// *******************************************************************************************
// **     Function: stack_nodes																**
// **   Parameters:	N/A																		**
// **       Return:	LinkedListNode															**
// **  Description: Returns the underlying linked list for the stack.						**
// *******************************************************************************************
template <class T>
typename Stack<T>::LinkedListNode* Stack<T>::stack_nodes() const
{
	return stack;
}

// *******************************************************************************************
// **     Function: size																	**
// **   Parameters:	N/A																		**
// **       Return:	int																		**
// **  Description: Returns the size of the stack.											**
// *******************************************************************************************
template <class T>
int Stack<T>::size()
{
	return stackSize;
}

// *******************************************************************************************
// **     Function: isEmpty																	**
// **   Parameters:	N/A																		**
// **       Return:	bool																	**
// **  Description: Returns if the stack is empty.											**
// *******************************************************************************************
template <class T>
bool Stack<T>::isEmpty() const
{
	return stackSize == 0;
}

// Explicit Objects that the Stack template class will work with
template class Stack<PlayerCard>;
template class Stack<InfectionCard>;
