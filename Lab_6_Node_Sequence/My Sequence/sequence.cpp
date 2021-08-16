#include <iostream>
#include <algorithm>
#include <cassert>
#include "sequence.h"
#include "node.h"

using namespace std;

namespace coen79_lab6
{
    //sets all values to null and zero and initializes the seq
    void sequence::init() {
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }

    //constucts a new sequence
    sequence::sequence() {
        init();
    }

    //constructs a new sequence based on the provided sequence
    sequence::sequence(const sequence& source) {
        init();
        *this = source;
    }

    //destructs the sequence and reinitializes the pointers
    sequence::~sequence() {
        list_clear(head_ptr);
        init();
    }

    //puts the cursor to the start of the seq
    void sequence::start() {
        precursor = head_ptr;
        cursor = head_ptr;
    }

    //puts the cursor to the end of the seq and the precur one before it
    void sequence::end() {
        if(many_nodes == 0) {
            cursor = NULL;
            precursor = NULL;
        } else if (head_ptr == tail_ptr) {
            cursor = head_ptr;
            precursor = NULL;
        } else {
            cursor = tail_ptr;
            precursor = list_locate(head_ptr, many_nodes-1);
        }
    }

    //advances the cursor and precursor forward one item if there is currently an item
    void sequence::advance() {
        assert(is_item());

        precursor = cursor;
        cursor = cursor->link();
    }

    //inserts an item prior to the current position
    void sequence::insert(const value_type& entry) {
        if(!is_item() || precursor == NULL) {
            list_head_insert(head_ptr, entry);
            if(tail_ptr == NULL) {
                tail_ptr = head_ptr;
            }
            cursor = head_ptr;
            precursor = NULL;
            many_nodes++;
        } else {
            list_insert(precursor, entry);
            cursor = precursor->link();
            many_nodes++;
        }
    }

    //attaches an item after the current position
    void sequence::attach(const value_type& entry) {
        if(head_ptr == NULL) {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;
            many_nodes++;
        } else if(cursor == NULL) {
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            tail_ptr = tail_ptr->link();
            cursor = tail_ptr;
            many_nodes++;
        } else {
            list_insert(cursor, entry);
            precursor = cursor;
            if(cursor == tail_ptr) {
                tail_ptr = tail_ptr->link();
            }
            cursor = cursor->link();
            many_nodes++;
        }
    }

    //sets the list equal to the source list
    void sequence::operator =(const sequence& source) {
        if(this == &source) {
            return;
        }
        
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes = source.many_nodes;
        start();
        node* cur = source.head_ptr;
        while(cur != source.cursor) {
            advance();
            cur = cur->link();
        }
    }

    //if there is an item, it is removed and the list is maintained
    void sequence::remove_current() {
        assert(is_item());

        if(head_ptr == cursor && head_ptr == tail_ptr) {
            list_head_remove(head_ptr);
            init();
        } else if(head_ptr == cursor && head_ptr != tail_ptr) {
            list_head_remove(head_ptr);
            precursor = NULL;
            cursor = head_ptr;
        } else if(cursor == tail_ptr) {
            list_remove(precursor);
            tail_ptr = precursor;
            cursor = NULL;
        } else {
            list_remove(precursor);
            cursor = precursor->link();
        }
        many_nodes--;
    }

    //returns the number of nodes in the seq
    sequence::size_type sequence::size() const {
        return many_nodes;
    }

    //returns true if there is an item pointed to by the cursor
    bool sequence::is_item() const {
        return (cursor != NULL);
    }

    //returns the data pointed to by the cursor
    sequence::value_type sequence::current() const {
        return cursor->data();
    }
}