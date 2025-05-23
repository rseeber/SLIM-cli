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
        printf("Usage: 'slim <options>'\nTry 'slim --help' for more.\n");
        return -1;
    }

    //before we actually perform actions, we need to load/create the user database
    initDB();
    int x = handler(argv[1], argc, argv);
    saveDB();

    return x;
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
        initCookieDB();
        cookie c;
        int x;
        x = loginAsUser(argv[2], argv[3], &c);
        //output cookie
        if(x >= 0){
            printf("token: %d\texpiry: %d\tuserID: %d\n", c.token, c.expiry, c.userID);
        }
        else{
            cout << "invalid login credentials!\n";
        }
        //save the updates cookies to the cookie file
        saveCookieDB();
        return x;
    }

    //logout
    //logs a user with the specified username out
    if(strcmp(verb, "logout") == 0){
        initCookieDB();
        // get the cookie from the username
        login l;
        cookie c;
        findUserByName(argv[2], &l);
        findCookieByUserID(l.userID, &c);

        //use the cookie to find their token, then revoke the token with logout()
        int userID = logout(c.token);
        printf("userID: %d\n", userID);
        //check if user is logged in.
        if(userID < 0){
            cout << "no such user logged in.\n";
            return userID;
        }
        //otherwise, return the userID
        cout << userID << endl;
        //save the new cookie set if changes were made
        saveCookieDB();
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
            initCookieDB();
            printCookieDB();
            //cout << getLoggedInUsers_string() << endl;
            return 0;
        }
        cout << "error: invalid operation. See 'slim list' documentation for more info.\n";
        return -1;
    }

    //findUser
    if(strcmp(verb, "findUser") == 0){
        login l;
        int x;
        // byName
        if(strcmp(argv[2], "byName") == 0){
            x = findUserByName(argv[3], &l);
        }
        //byID
        else if(strcmp(verb, "byID") == 0){
            int userID = atoi(argv[2]);
            x = findUserByID(userID, &l);
        }
        //no other option is supported - error
        else{
            cout << "Error: invalid operator for 'findUser'.\n";
            return -1;
        }
        //if the function call returned an error, don't print
        if(x < 0){
            return -1;
        }
        printUser(l);
        return 0;

    }

    //findCookie
    if(strcmp(verb, "findCookie") == 0){
        cookie c;
        int x;
        int userID;
        //byName
        if(strcmp(argv[2], "byName") == 0){
            string username = argv[3];
            //get the userID
            login l;
            if(findUserByName(username, &l) < 0){
                cout << "Error: couldn't find user '" << username << "' in DB.\n";
                return -1;
            }
            userID = l.userID;
        }
        //byID
        else if(strcmp(argv[2], "byID") == 0){    
            userID = atoi(argv[3]);
        }
        else{
            cout << "Error: invalid operation for 'findCookie'.\n";
            return -1;
        }
        printf("userID: %d\n", userID);
        cout << "whattttt\n";
        //now that we have the userID in both cases, do the work
        //if the function call returned an error, don't print
        if(findCookieByUserID(userID, &c) < 0){
            return -1;
        }
        //we need to create an interface func for printing cookies
        cout << "[0]: " << c.userID << "\t" << c.user << "\t" << c.token << "\t" << c.expiry << endl;
        cout << "aaahhh what\n";
        return 0;

    }

    //clear
    if(strcmp(verb, "clear") == 0){
        //users
        if(strcmp(argv[2], "users") == 0){
            //delete users file
            system("rm data/users.txt");
            //recall that SaveDB() is called after handler() returns.
            // so we need to just fully exit(), or find some other workaround
            // if this later becomes infeasible
            exit(0);    // return 0
        }

        //cookies
        if(strcmp(argv[2], "cookies") == 0){
            //delete the cookies file
            system("rm data/cookies.txt");  // dependancy on rm
            return 0;
        }

    }

    //if no key word recognized
    printf("%s: Invalid operator(s).\n", argv[0]);
    return -1;
}