#include <iostream>

#include "lib/login.hpp"
#include "funcs.hpp"
#include <string.h>

using namespace std;



int main(int argc, char** argv){

    /*
     * We will create a number of functions which are all in one wrappers
     * for the desired library calls. In this main() method, we will check the
     * cli input to determine which function they want. We will call that given
     * function by using a switch case.
    */

    if(strcmp("addUser", argv[1]) == 0){
        cli_addUser(argv[2], argv[3]);
    }

}