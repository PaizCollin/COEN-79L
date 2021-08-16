#include <iostream>
#include <cstring>

#include "bag_bst.h"

using namespace std;
using namespace coen79_lab9;

int main() {

    //positive tests
    //1
    bag<int> b1;

    //2
    b1.insert(5);
    b1.insert(3);
    b1.insert(7);
    b1.insert(4);
    b1.insert(6);
    b1.count(5)

    //3
    bag<int> b2(b1);
    b2.count(5);

    //4
    b1.erase_one(6);
    b1.count(6);

    //5
    b1.count(5);
    b1.insert(5);
    b1.insert(5);
    b1.insert(5);
    b1.count(5);
    b1.erase(5);
    b1.count(5);

    //6
    bag<int> b3;
    b3 = b2;

    //7
    b3 += b1;

    //8
    bag<int> b4;
    b4.insert_all(b3);
/*
    //negative tests
    //1
    bag b5;

    //2
    bag<int> b5;
    bag<char> b6(b5);

    //3
    b5.insert(5);
    b5.insert(6);
    b5.insert(7);
    b5.insert("yes");

    //4
    b5.erase_one(1);

    //5
    b5.erase(1);

    //6
    bag<char> b7;
    b7 = b5;

    //7
    bag<char> b8;
    b8 = b5;

    //8
    bag<char> b9;
    b9.insert_all(b5);
*/
    //boundary tests
    //1
    bag<int> b10;
    b10.erase(10);
    b10.erase_one(10);

    //2
    b10.count(10);

}