#include <string>
#include <cstring>
#include <iostream>

using namespace std;

//takes a string input from the user and outputs the number of alpha numeric and non alphanumeric characters
int main()
{
    char strarr[100];
    char *strptr;
    char ch;
    int alpha=0, other=0;
    string str1;

    cout << "Enter a string: ";     //prompts the user for a string input
    getline(cin, str1);         //obtains the string inputted by the user
    strcpy(strarr, str1.c_str());       //copies the string to the string array

    //iterates through a pointer to the string and checks if each character is alphanumeric or not
    for(strptr = strarr; *strptr != '\0'; strptr++) {
        ch = *strptr;

        //checks if the current character is alpha numeric. if yes: 'alpha' iterates, if a space: the loop continues, if not: increment 'other'
        if(isalpha(ch)) {
            alpha++;
        } else if(ch == ' ') {
              continue;
        } else {
            other++;
        }
    }

    cout << "Alpha Count: " << alpha << "\n";       //prints the number of alpha numeric characters in the provided string
    cout << "Non-Alpha Count: " << other << "\n";        //prints the number of non-alpha numeric characters in the provided string

}