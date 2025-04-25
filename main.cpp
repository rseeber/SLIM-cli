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
        printf("Usage: %s <options>\nTry %s --help for more.\n", argv[0], argv[0], argv[0]);
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
    //this func technically doesn't make any sense until we actually save
    // login cookies somewhere. For now, everyone logs out on program completion
    if(strcmp(verb, "logout") == 0){
        initCookieDB();
        //get token from argument
        unsigned int token = atoi(argv[2]); //need to do error checking !!
        int userID = logout(token);
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
            cout << getLoggedInUsers_string() << endl;
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
            //this call currently broken because findUserByID() asks for a list<login>::iterator
            //but findUserByName() asks for just a login*.
            //Uncomment when interface is fixed.
            
            //x = findUserByID(userID, &l);

            //work-around:
            list<login>::iterator it;
            x = findUserByID(userID, &it);
            l = *it;
        }
        else{
            cout << "Error: invalid operator for 'findUser'.\n";
            return -1;
        }
        //if the function call returned an error, don't print
        if(x >= 0){
            //switch this to printUser(l, 0) when interface is made public.
            cout << "[" << 0 << "]: " << l.user << "\t" << l.email << "\t" << l.passHash << "\t" << l.salt << endl;
            return 0;
        }
        return -1;

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
            findUserByName(username, &l);
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

        //now that we have the userID in both cases, do the work
        list<cookie>::iterator it;
        x = findCookieByUserID(userID, &it);
        c = *it;
        //if the function call returned an error, don't print
        if(x >= 0){
            //we need to create an interface func for printing cookies
            cout << "[0]: " << c.userID << "\t" << c.user << "\t" << c.token << "\t" << c.expiry << endl;
            return 0;
        }
        return -1;

    }

    //if no key word recognized
    printf("%s: Invalid operator(s).\n", argv[0]);
    return -1;
}