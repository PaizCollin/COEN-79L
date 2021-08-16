#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "random.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
    rand_gen::rand_gen(int inSeed, int inMultiplier, int inIncrement, int inModulus) {      //constructor

        seed = inSeed;
        multiplier = inMultiplier;
        increment = inIncrement;
        modulus = inModulus;

    } 

    //sets the new seed value
    void rand_gen::set_seed(int newSeed) {

        seed = newSeed;
    }

    //generates the next pseudorandom value
    int rand_gen::next() {

        int c;

        c = ((multiplier * seed + increment ) % modulus);
        seed = c;
        return c;
    }

    void rand_gen::print_info() {

        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
    }
}