// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    //constructor defaults
    statistician::statistician() { 
        size = 0;
        total = 0;
    }

    //next inputs the next value in the sequence and determines if it is a min or max
    void statistician::next(double r) {
        if(size == 0) {
            size = 1;
            total = r;
            min = r;
            max = r;
        } else {
            size++;
            total += r;

            if(r < min) {
                min = r;
            }

            if(r > max) {
                max = r;
            }
        }
    }

    //resets the sequence
    void statistician::reset() {
        size = 0;
        total = 0;
    }

    //returns the number of numbers in the sequence
    int statistician::length() const {
        return size;
    }

    //returns the sum of the numbers in the sequence
    double statistician::sum() const {
        return total;
    }

    //returns the mean of the numbers in the sequence
    double statistician::mean() const {
        return (total/size);
    }

    //returns the minimum value in the sequence
    double statistician::minimum() const {
        return min;
    }

    //returns the maximum value in the sequence
    double statistician::maximum() const {
        return max;
    }

    //overloads the addition binary operator to match the values in the statistician class and returns the values based on the performed operations
    statistician operator +(const statistician &s1, const statistician &s2) {

        statistician addResult;

        if(s1.length() == 0) {
            return s2;
        }

        if(s2.length() == 0) {
            return s1;
        }

        addResult.size = s1.length() + s2.length();
        addResult.total = s1.sum() + s2.sum();

        if(s1.minimum() < s2.minimum()) {
            addResult.min = s1.minimum();
        } else {
            addResult.min = s2.minimum();
        }

        if(s1.maximum() < s2.maximum()) {
            addResult.max = s2.maximum();
        } else {
            addResult.max = s1.maximum();
        }

        return addResult;
    }

    //overloads the multiplication binary operator to match the values in the statistician class and returns the values multiplied by the provided scale value
    statistician operator *(double scale, const statistician &s) {
        
        statistician multResult;


        if(s.length() == 0) {
            return s;
        }

        multResult.size = s.length();
        multResult.total = scale * s.sum();

        if(scale < 0) {
            multResult.min = scale * s.maximum();
            multResult.max = scale * s.minimum();
        } else {
            multResult.min = scale * s.minimum();
            multResult.max = scale * s.maximum();
        }

        return multResult;
    }

    //overloads the equivalent binary operator to match the values in the statistician class and returns true or false
    bool operator ==(const statistician &s1, const statistician &s2) {
        if(s1.length() != s2.length()) {
            return false;
        }

        if(s1.length() == 0) {
            return true;
        }
        
        return ((s1.length() == s2.length()) && (s1.mean() == s2.mean()) && (s1.minimum() == s2.minimum()) && (s1.maximum() == s2.maximum()) && (s1.sum() == s2.sum()));
    }
    
}


