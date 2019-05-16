#pragma once
#ifndef STACK_H
#define STACK_H



template<class T>
class Stack
{
	public:
		// LinkedListNode structure to hold the Stack data.
		struct LinkedListNode
		{
			T data;												// Stores the data for the linked list based off of the template date type.
			LinkedListNode* nextNode = nullptr;					// Holds a pointer to the next node in the linked list.
			LinkedListNode* previousNode = nullptr;				// Holds a pointer to the previous node in the linked list.
		};
	private:
		LinkedListNode* stack = nullptr;						// Holds the address for the head of the linked list
		LinkedListNode* bottomNode = nullptr;					// Holds the address for the last node of the linked list
		int stackSize = 0;										// Holds the size of the stack.
	public:
		// Constructors
		Stack();
		Stack(T);
		Stack(LinkedListNode*);

		// Destructor
		~Stack();

		// Stack public functions
		void push(T);
		void pop();
		void pop_back();
		T top();
		T bottom();
		bool contains(T);
		LinkedListNode* stack_nodes() const;
		int size();
		bool isEmpty() const;
};

#endif
