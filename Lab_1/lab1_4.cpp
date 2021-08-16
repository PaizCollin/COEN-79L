#include <cstring>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

//main function generates random numbers and counts the machines number of "guesses"
int main()
{
    string input;
    char ch[100];
    int guessCount;
    int guess;

    cout << "Think of a number 1 through 20. Press enter when you are ready \n";
    cin.get(); //waits for an enter key input

    //loop continues until the user indicates to the computer that its most recent randomly generated number (1-20) is the correct answer
    while(1) {
        srand(time(NULL));          //seed rand using the time
        guess = rand() % 21;            //generates number 1-20
        cout << "Is the number " << guess << "? Y or N \n";         //prompts the user for a string input
        getline(cin, input);         //obtains the string inputted by the user

        //checks if the user inputs a capital Y indicating the machine's guess was correct
        if(input == "Y") {
            guessCount++;
            cout << "I found the number in " << guessCount << " guesses! \n";
            break;
        } 

        //checks if the user makes a valid input (Y or N), else they will be notified
        if (input == "Y" || input == "N") {
            guessCount++;
            continue;
        } else {
            cout << "Please input either Y or N\n";
        }
        
        guessCount++;
    }

    return 0;
}