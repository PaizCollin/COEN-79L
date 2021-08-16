// FILE: main.cpp
// To test string class
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//

#include <iostream>
#include "mystring.h"

using std::cout;
using std::cin;
using std::endl;
using coen79_lab5::string;

std::string boolString(bool b) {
	return (b) ? "true" : "false";
}

int main(int argc, char const *argv[]) {
	string s1, s2("Nice to meet you"), s3(s2);
     cout << "s1: " << s1 << endl;
     cout << "s2: " << s2 << endl;
     cout << "s3: " << s3 << endl;
    
     cout << "*** += operator tests ***" << endl;
     cout << "s1 length: " << s1.length() << endl;
     s1 += string("~!");
     cout << "s1: " << s1 << endl;
     cout << "s1 length: " << s1.length() << endl;
    
     cout << "*** [] operator test ***" << endl;
     cout << "s1[0]: " << s1[0] << endl;
     cout << "s1[last]: " << s1[s1.length()-1]<<endl;
    
     cout << "*** = operator test ***" << endl;
     s2 = string("= Hello");
     cout << "s2: " << s2 << endl;
     cout << "s2: " << (s2 = string("= World")) << endl;

     string a = "a", b = "b";

     cout<<"a == b :" <<boolString(a==b) <<endl;
     cout<<"a+b : "<< a+ b<<endl;

     cout<<"Number of L's : "<<s2.count('l')<<endl;
     cout<<"Location of rl in s2: "<<s2.search(string("rl"))<<endl;
	return 0;
}
