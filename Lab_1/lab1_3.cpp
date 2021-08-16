#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//main func opens a file and prints it, excluding nonalpha characters and only printing words longer than 10 characters, in all uppercase
int main() 
{
    string word;
    char upperword[100];
    int length = 0;
    int i;
    char c;

    fstream filename;
    
    filename.open("lab1_file.txt"); //opens the file

    //checks if the file is open
    if(filename.is_open()) {
        while(filename >> word) {       //while there is still another word in the file
            for(i = 0; i < word.length(); i++) {        //for each letter in the word
                if((word[i] < 'A' || word[i] > 'z') || (word[i] < 'a' && word[i] > 'Z')) {      //if the letter is not alphanumeric, delete it
                    word.erase(i, 1);
                    i--;
                    continue;
                } 
                if(word.length() >= (10)) {         //if the word length is 10 or more, put the current letter in uppercase and print it (to be followed by the rest of the word's characters)
                    c = word[i];
                    putchar(toupper(c));
                }
            }
            if(word.length() >= 10){        //line break after the word
                cout << "\n";
            }

        }
    }

    return 0;
}