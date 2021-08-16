#include <iostream>     // Provides cout and cin
#include "sequence1.h"  // With value_type defined as double
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {

    //post: sequence contructor initializes the sequence
    sequence::sequence() {
        current_index = 0;
        used = 0;
    }

    //post: sets the current index of the sequence to the first space in the array
    void sequence::start() {
        current_index = 0;
    }

    //post: sets the current index of the sequence to the last element of the current sequence
    void sequence::end() {
        for(int i = (CAPACITY-1); i >= 0; i--) {
            current_index = i;
            if(is_item() == true) {
                break;
            }
        }
    }

    //sets the current index of hte sequence to the last space in the array
    void sequence::last() {
        current_index = CAPACITY - 1;
    }

    //pre: ensure there is an item in the current position
    //post: moves the current index of the sequence up one position
    void sequence::advance() {
        assert(is_item());
        if(current_index != (CAPACITY-1)) {
            current_index++;
        }
    }

    //post: moves the current index of the sequence down one position
    void sequence::retreat() {
        if(current_index != 0) {
            current_index--;
        }
    }

    //pre: ensure there is space in the array
    //post: inserts a new value in the sequence before the current item. if no current item, insert at the beginning of the sequence
    void sequence::insert(const value_type& entry) {
        assert(size() < CAPACITY);

        if(is_item() == false) {
            current_index = 0;
        } else {
            for(int i = used; i > current_index; i--) {
                data[i] = data[i-1];
            }
        }
        data[current_index] = entry;
        used++;
    }

    //pre: ensure there is space in the array
    //post: attaches a new value in the sequence following the current item. if no current item, attach at the end of the sequence
    void sequence::attach(const value_type& entry) {
        assert(size() < CAPACITY);

        if(used > 0) {
            for(int i = used-1; i > current_index; --i) {
                data[i+1] = data[i];
            }
            data[current_index+1] = entry;
            current_index++;
        } else {
            data[current_index] = entry;
        }
        used++;
    }

    //pre: ensure there is an item at the current index
    //post: removes the item at the current index and fills the gap by shifting proceeding items back one position
    void sequence::remove_current() {
        assert(is_item() == true);

        for(int i = current_index+1; i < used; i++) {
            data[i-1] = data[i];
        }
        used--;
        if(is_item() == false) {
            current_index = 0;
        }
    }

    //pre: ensure there is space in the array
    //post: inserts an item at the front of the array and shifts all other elements up one position
    void sequence::insert_front(const value_type& entry) {
        assert(size() < CAPACITY);

        for(int i = used; i >= 0; i--) {
            data[i] = data[i-1];
        }

        data[0] = entry;
        used++;
        current_index = 0;
    }

    //pre: sure there is space in the array
    //post: attaches an item at the back of the sequence
    void sequence::attach_back(const value_type& entry) {
        assert(size() < CAPACITY);

        data[used] = entry;
        current_index = used;
        used++;
    }

    //pre: ensure that there is an item at the first element in the array
    //post: removes the first element in the array and shifts all proceeding items back one position
    void sequence::remove_front() {
        current_index = 0;
        assert(is_item() == true);

        for(int i = 0; i < used; i++) {
            data[i-1] = data[i];
        }
        used--;
    }

    //post: returns sequence lhs as a sequence that contains all values of lhs, proceeded by all values of the sequence rhs
    sequence operator +=(sequence& lhs, sequence& rhs) {
        rhs.start();
        for(int i = 0; i < rhs.size() - 1; i++) {
            lhs.attach(rhs.current());
            rhs.advance();
        }
        return lhs;
    }

    //post: returns the number of items in the array
    sequence::size_type sequence::size() const {
        return used;
    }

    //post: returns true if there is an item at the current index, false otherwise
    bool sequence::is_item( ) const {
        return (current_index < used);
    }

    //pre: ensures there is an item at the current position
    //post: returns the value of the item at the current position
    sequence::value_type sequence::current() const {
        assert(is_item() == true);
        return data[current_index];
    }

    //pre: ensures that the index provided is less than the number of items used
    //post: returns the value of the item at the requested position 'index'
    sequence::value_type sequence::operator[](int index) const {
        assert(index < used);
        return data[index];
    }

    //post: returns the mean of all values in the sequence
    double sequence::mean() const {
        double sum;

        for(int i = 0; i < used; i++) {
            if(is_item() == true) {
                sum += data[i];
            }
        }
        cout << sum/used << endl;
        return sum/used;
    }

    //post: returns the standard deviation of all values in the sequence
    double sequence::standardDeviation() const {
        int sum = 0;
        for(int i = 0; i < used; i++) {
            sum += data[i];
        }
        double mean = (double)sum / (double)used;

        double sqDiff = 0;
        for(int j = 0; j < used; j++) {
            sqDiff += (data[j] - mean) * (data[j] - mean);
        }

        cout << (sqrt(sqDiff/used)) << endl;
    }

    //post: adds the value of the rhs sequence to the end of the sequence on the left, and returns it as a new sequence
    sequence operator +(const sequence& lhs, const sequence& rhs) {
        sequence newSeq(lhs);
        sequence right(rhs);
        right.start();
        for(int i = 0; i < right.size(); i++) {
            newSeq.attach(right.current());
            right.advance();
        }
        return newSeq;
    }

    //post: returns the sum of all the values in the sequence
    sequence::value_type summation(const sequence &s) {
        sequence t(s);
        t.start();
        int sum = 0;
        for(int i = 0; i < t.size(); i++) {
            sum += t.current();
            t.advance();
        }
        return sum;
    }

}