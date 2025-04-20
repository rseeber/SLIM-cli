#include <iostream>
#include <stdio.h>
#include <string.h>

#include "lib/login.hpp"

using namespace std;

list<login> myLogins;
list<cookie> myCookies;

int handler(int argc, char** argv);

int main(int argc, char** argv){
    //not enough options
    if (argc <= 2){
        printf("%s: Usage: %s <options>\n Try %s --help for more.\n", argv[0], argv[0], argv[0]);
        return -1;
    }

    //before we actually perform actions, we need to load/create the user database
    initDB();
    int x = handler(argc, argv);
    saveDB();
}

int handler(int argc, char** argv){
    char* verb = argv[1];
    
    // addUser
    if(strcmp(verb, "addUser") == 0){
        return addUser(argv[2], argv[3], argv[4]);
    }

    // editUser
    if(strcmp(verb, "editUser") == 0){
        //username
        if(strcmp(argv[2], "username") == 0){
            return editUsername(atoi(argv[3]), argv[4]);
        }
        //password
        if(strcmp(argv[2], "password") == 0){
            return editPasswd(atoi(argv[3]), argv[4]);
        }
        //email
        if(strcmp(argv[2], "email") == 0){
            return editEmail(atoi(argv[3]), argv[4]);
        }
    }

    // login
    if(strcmp(verb, "login") == 0){
        cookie c;
        int x;
        x = loginAsUser(argv[2], argv[3], &c);
        //output cookie
        printf("%d\t%d\t%d\n", c.token, c.expiry, c.userID);
        return x;
    }

    //logout
    if(strcmp(verb, "logout") == 0){
        //it would seem this feature isn't available in version 0.0.1-alpha of the library
        //TODO: handle
        cookie c;
        // c = dearmourCookie();
        return logout(c);
    }

    // deleteUser
    if(strcmp(verb, "deleteUser") == 0){
        // again, not available in version 0.0.1-alpha
        return -1;
    }

    // verifyToken
    if(strcmp(verb, "verifyToken") == 0){
        //not available yet
        return -1;
    }

    //if no key word recognized
    printf("%s: Invalid operator(s).\n", argv[0]);
    return -1;
}