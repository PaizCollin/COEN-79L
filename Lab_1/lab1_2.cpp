#include <cstring>
#include <iostream>
#include <iomanip>
#include <assert.h>


using namespace std;

//function reverses a 10 digit input
void reverse(string &output)
{
    int i;

    //iterates halfway through the 10 digits and swaps each digit with the digit on the "otherside" of the string input
    for(i=0; i<5; i++) {
        swap(output[i], output[10-i-1]);
    }


}

//main function requests and input and prints an output
int main()
{
    string input;

    cout << "Enter a string of 10 digits (no spaces): \n";     //prompts the user for a string input
    getline(cin, input);         //obtains the string inputted by the user
    string output = input;
    assert(input.length() == 10);

    reverse(output);         //calls function 'reverse'

    //iterates by two to print out the backward and forward strings in a diagonal column
    for(int i=0; i<10; i+=2) {
        int width = i+15;
        cout << setw(width) << input << setw(20) << output << "\n";
    }

    return 0;
}