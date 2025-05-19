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
     * Inside of def.hpp, we have a map that links string's to function pointers.
     * This allows us to convert an inputted parameter (ex 'addUser') to a specific
     * function to call dynamically.
     * 
     * In the mapped to functions, we call the library functions, as well as any necessary
     * setup required, such as initializing the DB.
     */

    string command = argv[1];

    auto it = options.find(command);
    if(it == options.end()){
        //not found
        return -1;
    }
    functionPointer fp = it->second;

    return fp(argv + 2);
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