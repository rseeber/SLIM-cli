#include <iostream>
#include <stdio.h>
#include <string.h>

#include "lib/login.hpp"

using namespace std;

list<login> myLogins;
list<cookie> myCookies;

int handler(char* verb, int argc, char** argv);

int main(int argc, char** argv){
    //not enough options
    if (argc <= 2){
        printf("%s: Usage: %s <options>\n Try %s --help for more.\n", argv[0], argv[0], argv[0]);
        return -1;
    }

    //before we actually perform actions, we need to load/create the user database
    initDB();
    int x = handler(argv[1], argc, argv);
    saveDB();
}

int handler(char* verb, int argc, char** argv){
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
        cout << "Error: invalid operation for 'editUser'.\n";
        return -1;
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
    //this func technically doesn't make any sense until we actually save
    // login cookies somewhere. For now, everyone logs out on program completion
    if(strcmp(verb, "logout") == 0){
        //get token from argument
        unsigned int token = atoi(argv[2]);
        int userID = logout(token);
        //check if user is logged in.
        if(userID < 0){
            cout << "no such user logged in.\n";
            return userID;
        }
        //otherwise, return the userID
        cout << userID << endl;
        return 0;
    }

    // deleteUser
    if(strcmp(verb, "deleteUser") == 0){
        //get userID from argument
        //NOTE: atoi doesn't do error checking, need to switch to strtol() or smthn
        int userID = atoi(argv[2]);
        return deleteUser(userID);
    }

    // verifyToken
    if(strcmp(verb, "verifyToken") == 0){
        //get token from argument
        int token = atoi(argv[2]);
        return validateToken(token);
    }

    //list
    if(strcmp(verb, "list") == 0){
        //users
        if(strcmp(argv[2], "users") == 0){
            printDB();
            return 0;
        }
        //cookies
        if(strcmp(argv[2], "cookies") == 0){
            cout << getLoggedInUsers_string() << endl;
            return 0;
        }
        cout << "error: invalid operation. See 'slim list' documentation for more info.\n";
        return -1;
    }

    //if no key word recognized
    printf("%s: Invalid operator(s).\n", argv[0]);
    return -1;
}