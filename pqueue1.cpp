/*

FILE: pqueue1.cpp
DESCRIPTION: This file implements the class PriorityQueue. 
*/

#include "stdafx.h"		// Includes the standard includes 
#include <iostream>		
#include "pqueue1.h" 	

using namespace std;	


// CONSTRUCTOR 
PriorityQueue::PriorityQueue( )
{	
	head_ptr = NULL;		
	many_nodes = 0;			
}
 
// COPY CONSTRUCTOR 
PriorityQueue::PriorityQueue(const PriorityQueue& source)
{	
	if (source.head_ptr == NULL)
	{
		head_ptr = NULL;
		many_nodes = 0;
	}
	else
	{
		head_ptr = new Node;
		head_ptr->link = NULL;
		Node *iter = head_ptr, *sIter = source.head_ptr;

		for (int i = 0; i < source.many_nodes - 1; i++)
		{
			iter->data = sIter->data;
			iter->priority = sIter->priority;


			iter->link = new Node;
			iter = iter->link;
			sIter = sIter->link;
		}

		iter->data = sIter->data;
		iter->priority = sIter->priority;
		iter->link = NULL;
	}

	many_nodes = source.many_nodes;
}

// DESTRUCTOR
PriorityQueue::~PriorityQueue( ) 
{
	Node *previous,
		*current = head_ptr;

	while (current != NULL)
	{
		previous = current;
		current = current->link;
		delete previous;
	}
}

// OVERLOADED ASSIGNMENT OPERATOR
void PriorityQueue::operator =(const PriorityQueue& source)
{
	//self-assignment case:
	if (this == &source) return;

	//deallocate queue
	//second iterator / source iterator, *this iterator
	Node *sIter, *iter = head_ptr;

	while (iter != NULL)
		//deallocate original queue
	{
		sIter = iter;
		iter = iter->link;
		delete sIter;
	}

	if (source.head_ptr == NULL)
		//reset head_ptr
	{
		head_ptr = NULL;
	}
	else
	{
		iter = head_ptr = new Node;
		sIter = source.head_ptr;

		//rebuild queue, copying values from source
		for (int i = 0; i < source.many_nodes - 1; i++)
			//copy values for current item
		{
			iter->data = sIter->data;
			iter->priority = sIter->priority;

			//create next node for new queue
			iter->link = new Node;
			//advance for next copy
			iter = iter->link;
			sIter = sIter->link;
		}
		//at this point, we are at the tail end
		//so we do not create a new node
		iter->data = sIter->data; //copy values
		iter->priority = sIter->priority;
		iter->link = NULL; //tail end of queue
	}

	many_nodes = source.many_nodes;
}
 
 
void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
	// Create a new node with data and priority ranking
	Node *target_ptr = new Node();
	target_ptr->data = entry;
	target_ptr->priority = priority;

	// If the queue is empty, the new (and only) node is at the front of the list 
	if(is_empty())
	{
		head_ptr = target_ptr;
		head_ptr->link = NULL;
	}
  
	// Else the queue is not empty
	else if(!is_empty())
	{
		// Create a new temporary pointer to traverse through the list
		Node *cursor = head_ptr;		
		int counter1 = 0, counter2 = 0;

		// Traverse the length of the list
		for (counter1; counter1 < size(); ++counter1)
		{ 
			// If the cursor node's priority is less than this node's priority
			if(cursor->priority < priority)
			{	
				target_ptr->link = cursor;			// Link the cursor node

				// However, if cursor node is at the front, then this node is at the front
				if(cursor == head_ptr)
				{
					head_ptr = target_ptr;
				}

				cursor = head_ptr;					// Bring cursor back to the front

				// Check the list as we traverse
				for(counter2; counter2 < counter1; ++counter2)
				{
					if(counter2 == (counter1 - 1))
					{
						cursor->link = target_ptr;
						break;
					}
					
					cursor = cursor->link;
				}
				break;
			}
			// Else if not less in priority
			else if(counter1==(size()-1))
			{
				cursor->link = target_ptr;
				target_ptr -> link = NULL;
			}
			cursor = cursor->link;
		}
 
	}
	++many_nodes;		// Increment node count
}


PriorityQueue::Item PriorityQueue::get_front()
{
	if (many_nodes > 0)
	{
		Node *temp = head_ptr;

		//set new head of list
		head_ptr = head_ptr->link;
		//save data field for returning
		Item frontItem = temp->data;

		//deallocate memory
		delete temp;
		//one item less in queue
		many_nodes--;
		//return data
		return frontItem;
	}
}
 
