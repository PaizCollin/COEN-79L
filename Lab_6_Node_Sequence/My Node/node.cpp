// FILE: node.cpp
//
//
//  COEN 79
//  --- Farokh Eskafi, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
	const node *cursor;
	size_t answer;

	answer = 0;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;

	return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

	//creates a new list with the items from start to end-1
	void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr) {
		head_ptr = NULL;
		tail_ptr = NULL;

		if(start_ptr == end_ptr || start_ptr == NULL) {
			return;
		}

		list_head_insert(head_ptr, start_ptr->data());
		tail_ptr = head_ptr;

		while(start_ptr != NULL && start_ptr->link() != end_ptr) {		//while start and start link arent null or at the end, insert the node into the new list
			start_ptr = start_ptr->link();
			list_insert(tail_ptr, start_ptr->data());
			tail_ptr = tail_ptr->link();
		}
	}

	//returns the occurences of target in the list
    size_t list_occurrences(node* head_ptr, const node::value_type& target) {
		if(head_ptr == NULL) {
			return 0;
		}

		int count = 0;
		node* cursor;

		for (cursor = head_ptr; cursor != NULL; cursor = cursor->link()) {	//while cursor isnt null, increase count if the cursor data equals the target data
			if (target == cursor->data()) {
				count++;
			}
		}

		return count;
	}

	//inserts the entry at the position in the list, if the position is valid
    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) {
		assert((position > 0) && (position <= list_length(head_ptr) +1));

		if(position == 1) {
			list_head_insert(head_ptr, entry);
		} else if (position == list_length(head_ptr) + 1) {
			list_insert(list_locate(head_ptr, list_length(head_ptr)), entry);
		} else {
			list_insert(list_locate(head_ptr, position - 1), entry);
		}
	}

	//removes the item at the desired position, if the position is valid and the list isnt empty
    node::value_type list_remove_at(node*& head_ptr, size_t position) {
		assert((head_ptr != NULL) && (position > 0) && (position <= list_length(head_ptr) +1));

		node::value_type temp;

		if(position == 1) {
			temp = head_ptr->data();
			list_head_remove(head_ptr);
		} else {
			node *cursor = list_locate(head_ptr, position-1);
			temp = cursor->data();
			list_remove(cursor);
		}
		return temp;
	}

	//copies a segment of a list into another list and returns the head ptr of the new list
    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) {
		assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
		if(head_ptr == NULL) {
			return NULL;
		}

		node* start_ptr = list_locate(head_ptr, start);
		node* end_ptr = list_locate(head_ptr, finish + 1);
		node* head = NULL;
		node* tail = NULL;
		list_piece(start_ptr, end_ptr, head, tail);

		return head;
	}	

	//prints the values pointed to be the nodes in the list
    void list_print (const node* head_ptr) {
		if(head_ptr == NULL) {
			cout << endl;
			return;
		}
		while(head_ptr != NULL) { 		//while the head ptr isnt null, print the data
			cout << head_ptr->data();
			if(head_ptr->link() != NULL) {
				cout << ", ";
			}
			head_ptr = head_ptr->link();
		}
		cout << endl;
	}

	//removes the duplicate values that are pointed to in the list
    void list_remove_dups(node* head_ptr) {
		if(head_ptr == NULL) {
			return;
		}

		node *cursor = head_ptr;
		node *dup = cursor;
		while(cursor != NULL) {		//while the cursor isnt null, go to each dup
			dup = cursor;
			while(dup->link() != NULL) {	//while the dup link isnt null, crossref with all other data and remove any repeats
				if(cursor->data() == dup->link()->data()) {
					list_remove(dup);
				} else {
					dup = dup->link();
				}
			}
			cursor = cursor->link();
		}
	}

	//detects when a loop in the list is initiated, and returns that starting position if it exists, else NULL
    node* list_detect_loop (node* head_ptr) {
		if(head_ptr == NULL) {
			return NULL;
		}

		node *cursor1 = head_ptr;
		node *cursor2 = head_ptr;
		bool loop = 0;

		while(cursor2 != NULL && cursor2->link() != NULL) {		//while cursor2 and the link arent null, identify a loop
			cursor2 = cursor2->link()->link();
			cursor1 = cursor1->link();
			if(cursor1 == cursor2) {
				loop = true;
				break;
			}
		}

		if(loop == false) {
			return NULL;
		}

		cursor1 = head_ptr;
		while(cursor1 != cursor2) {		//while cursor1 isnt cursor2, move forward, to find the start of the loop
			cursor1 = cursor1->link();
			cursor2 = cursor2->link();
		}

		return cursor1;
	}
}
