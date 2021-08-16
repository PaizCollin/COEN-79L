#include <iostream>
#include "deque.h"

using namespace coen79_lab8;

int main(int argc, const char * argv[]) {
    
    //positive tests
    //1
    coen79_lab8::deque<int> d1;  
    
    //2
    for (int i = 0; i < 30; ++i) {
        d1.push_back(i);
        std::cout << d1.back() << " ";
    }
    std::cout << std::endl;
    
    //3
    for (int i = 0; i < 30; ++i) {
        d1.push_front(i);
        std::cout << d1.front() << " ";
    }
    std::cout << std::endl;

    //4
    for (deque<int>::iterator it = d1.begin(); it != d1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    //5
    for (int i = 0; i < 5; ++i) {
        d1.pop_back();
    }

    for (deque<int>::iterator it = d1.begin(); it != d1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
     
    //6
    for (int i = 0; i < 10; ++i) {
        d1.pop_front();
    }

    for (deque<int>::iterator it = d1.begin(); it != d1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    //7
    coen79_lab8::deque<int> d2;
    d2.push_front(3);
    d2.push_front(2);
    d2.push_front(1);
    d2.push_back(4);
    d2.push_back(5);
    d2.push_back(6);

    coen79_lab8::deque<int> d3;
    d3 = d2;

    for (deque<int>::iterator it = d3.begin(); it != d3.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
     
    //8
    coen79_lab8::deque<int> d4(d1);

    for (deque<int>::iterator it = d4.begin(); it != d4.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    //negative tests
    //1
    //coen79_lab8::deque d5;

    //2
    //coen79_lab8::deque<int> d5;
    //d5.push_front("Yes");

    //3
    //d5.push_back("Yes");

    //4
    coen79_lab8::deque<int> d6;
    //d6.pop_front();

    //5
    //d6.pop_back();

    //6
/*  for (deque<int>::iterator it = d6.begin(); it != it++; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
*/

    //7
    coen79_lab8::deque<char> d7;
    //d6 = d7;

    //8
    //coen79_lab8::deque<char> d8(d6);

    //boundary tests
    //1
    coen79_lab8::deque<int> d9;
    for(int i = 0; i < 20; i++) {
        d9.push_front(i);
        std::cout << d9.front();
    }
    std::cout << std::endl;

    //2
    coen79_lab8::deque<int> d10;
    for(int i = 0; i < 20; i++) {
        d10.push_back(i);
        std::cout << d10.back();
    }
    std::cout << std::endl;

    //end of tests
}
