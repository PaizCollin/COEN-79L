#include "mystring.h"
#include <iostream>
#include <cassert>
#include <string.h>

namespace coen79_lab5
{
    //post: constructs a string based on the char array argument
    string::string(const char str[ ]) {
        current_length = strlen(str);
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, str, allocated);
    }

    //post: constructs a string based on the single char argument
    string::string(char c) {
        current_length = 1;
        allocated = 2;
        characters = new char[allocated];
        characters[0] = c;
        characters[1] = '\0';
    }

    //post: constructs a string based on the source string argument
    string::string(const string& source) {
        current_length = source.length();
        allocated = current_length + 1;
        characters = new char[allocated];
        strncpy(characters, source.characters, allocated);
    }

    //post: override destructor to deallocate the characters pointed to by the array
    string::~string( ) {
        delete [] characters;
    }

    //post: addend is aadded to the end of the string
    void string::operator +=(const string& addend) {
        current_length = current_length + addend.current_length;
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend.characters, addend.current_length);
    }

    //post: addend is added to the end of the string
    void string::operator +=(const char addend[ ]) {
        current_length = current_length + strlen(addend);
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
    }

    //post: the char is added to the end of the string
    void string::operator +=(char addend) {
        current_length++;
        allocated = current_length + 1;
        reserve(allocated);
        characters[current_length-1] = addend;
        characters[current_length] = '\0';
    }

    //post: allocates new space based on the provided positive integer 
    void string::reserve(size_t n) {
        char *newchars;
        newchars = new char[n];
        strncpy(newchars, characters, current_length);
        allocated = n;
        delete [] characters;
        characters = newchars;
    }

    //post: returns a string that is equal to the source, by deleting the original and then allocating the space of the source
    string& string::operator =(const string& source) {
        this->dlt(0, current_length);
        if(current_length != source.current_length) {       //if the current length isnt long enough, reserve space for it
            allocated = source.allocated;
            reserve(allocated);
        }
        strncpy(characters, source.characters, source.current_length);
        current_length = source.current_length;
        return *this;
    }

    //pre: position is less than or equal to the length
    //post: inserts the source string into the string starting at the position provided in the second argument
    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());
        int newlength = source.current_length + current_length;
        if(allocated < (newlength)) {        //reserve space for the new items to be inserted
            reserve(newlength);
        }
        for(int i = length(); i >= position; i--) {        //move each char forward to make room for the new characters
            characters[i] = characters[i-1];
        }
        for(int j = 0; j < source.length(); j++) {        //insert the new characters starting at the position
            characters[j+position] = source.characters[j];
        }
        current_length = (newlength);
    }

    //pre: the sum of the position and the number of to be deleted items is less than the length of the string
    //post: deletes this characters
    void string::dlt(unsigned int position, unsigned int num) {
        assert((position + num) <= length());
        for(int i = position; i < (position + num); i++) {        //move each character back to replace the ones to be deleted
            characters[i] = characters[i+num];
        }
        current_length = current_length - num;
    }

    //pre: the position provided is a valid position in the string
    //post: replaces the char in the position with the char c
    void string::replace(char c, unsigned int position) {
        assert(position < length());
        characters[position] = c;
    }

    //pre: the length is greater than or equal to the length of the source + the position
    //post: replaces the characters starting at a position in the string
    void string::replace(const string& source, unsigned int position) {
        assert((position + source.length()) <= length());
        for(int i = position; i < source.length(); i++) {       //goes through each character and replaces them with the source
            characters[i] = source.characters[i - position];
        }
    }

    //pre: the position exists in the length of the string
    //post: returns the char in the position provided
    char string::operator [ ](size_t position) const {
        assert(position < length());
        return characters[position];
    }

    //post: returns the position of the char c to be searched for. if not, return -1
    int string::search(char c) const {
        int i = 0;
        while(i < allocated) {
            if(characters[i] == c) {
                return i;
            }
            i++;
        }
        return -1;
    }

    //post: checks the string for a substring. returns the start position, if not return -1
    int string::search(const string& substring) const {
        for(size_t i = 0; i < (current_length - substring.current_length) + 1; i++) {
            if(strncmp(&characters[i], substring.characters, substring.current_length) == 0) {
                return i;
            }
        }
        return -1;
    }

    //post: returns the number of characters matching c
    unsigned int string::count(char c) const {
        unsigned int count = 0;
        for(size_t i = 0; i < current_length; i++) {      //go through all char
            if(characters[i] == c) {
                count++;
            }
        }
        return count;
    }
    
    //friend functions for boolean expressions between two strings
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        outs << source.characters;
        return outs;
    }

    bool operator ==(const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters) == 0);
    }

    bool operator !=(const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters) != 0);
    }

    bool operator > (const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters) > 0);
    }

    bool operator < (const string& s1, const string& s2) {
        return(strcmp(s1.characters, s2.characters) < 0);
    }

    bool operator >=(const string& s1, const string& s2) {
        return((s1>s2) || (s1==s2));
    }

    bool operator <=(const string& s1, const string& s2) {
        return((s1<s2) || (s1==s2));
    }

    //add two strings together and returns the new string
    string operator +(const string& s1, const string& s2) {
        string newstr;
        newstr += s1;
        newstr += s2;
        return newstr;
    }

    //add a char to the end of a string and return the new string
    string operator +(const string& s1, const char addend[ ]) {
        string newstr;
        newstr += s1;
        newstr += addend;
        return newstr;
    }

    //take input for a string and return ins
    std::istream& operator >> (std::istream& ins, string& target) {
        char *in = new char[100];
        while (ins && isspace(ins.peek())) {
            ins.ignore();
        }
        ins >> in;
        target = string(in);
        return ins;     
    }

}