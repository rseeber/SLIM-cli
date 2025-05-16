#include <iostream>
#include <string.h>
#include <vector>
#include <map>

#include "lib/login.hpp"
#include "funcs.hpp"
#include "def.hpp"

using namespace std;



int main(int argc, char** argv){

    /*
     * We will create a number of functions which are all in one wrappers
     * for the desired library calls. In this main() method, we will check the
     * cli input to determine which function they want. We will call that given
     * function by using a switch case.
    */



    /*
     * Create an array functions[] = {"[func1]", "[func2]", ..., "[funcn]"}.
     * Get a user inputted string called verb. Find the index s.t. 
     * functions[i] == verb.
     * 
     * Use that i as the integer encoding for the string, or -1 on no match.
    */

    string command = argv[1];

    auto it = options.find(command);
    if(it == options.end()){
        //not found
        return -1;
    }
    functionPointer fp = it->second;

    return fp(argv);
}

int getIndex(const vector<string> myList, const string key){
    //iterate through each element
    for(int i = 0; i < myList.size(); ++i){
        //if the element exists at the given index, return the index
        if(myList.at(i) == key){
            return i;
        }
    }
    //if not found, return -1
    return -1;
}