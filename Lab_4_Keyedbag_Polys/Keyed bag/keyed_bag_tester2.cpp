//
//  COEN 79
//  
//

#include <iostream>
#include "keyed_bag.h"

using namespace std;
using coen79_lab4::keyed_bag;

void Insert(const int val, const string& key, keyed_bag& kb) {
    cout << "Inserting "<<val<<" with key \""<<key<<"\"." << endl;
    kb.insert(val, key);
}

void Erase(const string& key, keyed_bag& kb) {
    cout << "Erasing \""<< key <<"\"." << endl;
    kb.erase(key);
}

void Get(const string & key, const keyed_bag& kb) {
    cout << "Value for \""<<key<<"\": " << kb.get(key) << endl;
}

void Has(const string & key, const keyed_bag& kb) {
    cout << "Has "<<key<<": " << kb.has_key(key) << endl;
}

void Count(const int val, const keyed_bag& kb) {
    cout << "Number of "<< val <<"'s in the bag: " << kb.count(val) << endl;
}

void bSize(const keyed_bag& kb) {
    cout << "Bag size: " << kb.size() << endl;
}

int main(int argc, char const *argv[]) {
    keyed_bag kb1, kb2;

    //insert tests
    Insert(5,"five",kb1);
    Insert("yes", xyz ,kb1);
    Insert(INT_MAX,"max",kb1);

    //test has
    Has("five", kb1);
    Has(2, kb1);
    Has("six", kb1);

    //test get
    Get("five", kb1);
    Get("six", kb1);

    keyed_bag kbget;
    Insert(1,"one",kbget);
    Insert(2,"two",kbget);
    Insert(3,"three",kbget);
    Insert(4,"four",kbget);
    Insert(5,"five",kbget);
    Insert(6,"six",kbget);
    Get("six", kb1);

    //test size
    bSize(kb1);
    bSize(kb1000);
    bsize(kb2);

    //test count
    Count(5, kb1);
    Count("no", kb1)
    Count(1, kb1)

    //bool erase tests
    keyed_bag kb8;
    Insert(5,"five",kb8);
    Erase("five", kb8);

    Insert(5,"five",kb8);
    Insert(5,"five",kb8);
    Erase("five", kb8);

    Insert(INT_MAX, "max", kb8);
    Erase("max",kb8);

    //erase test
    keyed_bag kb9;
    Insert(5,"five",kb9);
    kb9.erase();

    keyed_bag kb10;
    kb10.erase();

    keyed_bag kb11;
    Insert(INT_MAX, "max", kb11);
    kb10.erase();

    //test duplicate
    keyed_bag kb4, kb5;
    Insert(5, "five", kb4);
    Insert(5, "five", kb5);
    kb4.hasDuplicateKey(kb5);

    keyed_bag kb99;
    kb99.hasDuplicateKey(kbdontexist);

    kb4.hasDuplicateKey(kb99);

    //test +
    keyed_bag kb3;
    kb3 = kb1 + kb2;
    kb3 = kb1 + 4;

    keyed_bag kb222, kb333, kb444;
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb222);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);
    Insert(5,"five",kb333);

    kb444 = kb222 + kb333;    


    //test +=
    kb1 += kb2;
    kb1 += 55;
    kb222 += kb333;

    return 0;
}
