// FILE: pqueue1.h
// CLASS PROVIDED: PriorityQueue (a priority queue of items)
//
// TYPEDEF for the PriorityQueue class:
//   typedef _____ Item 
//     The type Item is the data type of the items in the Priority Queue.
//     It may be any of the C++ built-in types (int, char, etc.), or a class 
//     with a default constructor, a copy constructor, and assignment operator.
//
// CONSTRUCTOR for the PriorityQueue class:
//   PriorityQueue( )
//     Postcondition: The PriorityQueue has been initialized with no Items.
//
// MODIFICATION MEMBER FUNCTIONS for the PriorityQueue class:
//   void insert(const Item& entry, unsigned int priority)
//     Postcondition: A new copy of entry has been inserted with the specified
//     priority.
//
//   Item get_front( )
//     Precondition: size( ) > 0.
//     Postcondition: The highest priority item has been returned and has been
//     removed from the PriorityQueue. (If several items have equal priority,
//     then the one that entered first will come out first.)
//
// CONSTANT MEMBER FUNCTIONS for the PriorityQueue class:
//   size_t size( ) const
//     Postcondition: Return value is the total number of items in the
//     PriorityQueue.
//
//   bool is_empty( ) const
//     Postcondition: Return value is true if the PriorityQueue is empty.
//
// VALUE SEMANTICS for the PriorityQueue class:
//   Assignments and the copy constructor may be used with
//   PriorityQueue objects

#ifndef PQUEUE_H			
#define PQUEUE_H
#include <stdlib.h> // Provides size_t

    struct Node; // This will be completely defined below.

    class PriorityQueue
    {
    public:
        typedef int Item;			// Integer items in the Priority Queue
        PriorityQueue( );			// Constructor
        PriorityQueue(const PriorityQueue& source);		// Copy constructor 
        ~PriorityQueue( );								// Destructor
        void operator =(const PriorityQueue& source);	// Overloaded assignment operator
        size_t size( ) const { return many_nodes; }		// Return the number of items in the PriorityQueue
        void insert(const Item& entry, unsigned int priority);			// Insert an item in the PriorityQueue
        Item get_front( );											// The highest priority item has been returned and has been 
        															// 	removed from the PriorityQueue. 
        bool is_empty( ) const { return many_nodes == 0; }			// Return value is true if the PriorityQueue is empty.
    private:
        // Note: head_ptr is the head pointer for a linked list that
        // contains the items along with their priorities. These nodes are
        // kept in order from highest priority (at the head of the list)
        // to lowest priority (at the tail of the list). The private member
        // variable, many_nodes, indicates how many nodes are on the list.
        // The data type Node is completely defined below.
        Node* head_ptr;				// This is the head pointer, which is a pointer to a Node
		size_t many_nodes;			// This is the counter to hold the number of items in the PriorityQueue
    };

    struct Node
    {   // Node for a linked list
        PriorityQueue::Item data;		// Data in the node
        unsigned int priority;			// Rank items based on their priority
        Node *link;						// Link to the next node
    };

#endif
