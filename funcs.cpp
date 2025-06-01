#include <iostream>
#include <stdio.h>
#include "lib/login.hpp"
using namespace std;


//modify DB

// (username, password) creates a user as specified, adding them to the DB
int cli_addUser(char** args){
    initDB();
    //don't use emails that's stupid we don't need them
    int flag = addUser(args[0], "default@email", args[1]);
    saveDB();
    return flag;
}

// input username and newPass. Updates the user's info if they exist.
// NOTE: Library imlimentation is broken currently
int cli_editPasswd(char** args){
    initDB();

    login l;
    if(findUserByName(args[0], &l) < 0){
        return -1;
    }

    editPasswd(l.userID, args[1]);
    saveDB();
    return 0;
}

// input username and newUsername. Updates the user's info if they exist.
// NOTE: Library imlimentation is broken currently
int cli_editUsername(char** args){
    initDB();

    login l;
    if(findUserByName(args[0], &l) < 0){
        return -1;
    }
    printf("username pre-edit: %s\n", l.user);

    if(editUsername(l.userID, args[1]) < 0){
        return -1;
    }

    printf("username post-edit: %s\n", l.user);
    saveDB();
	return 0;
}

// (username) self explanatory
int cli_deleteUser(char** args){
    initDB();
    login l;
    if(findUserByName(args[0], &l) < 0){
        return -1;
    }
    deleteUser(l.userID);
    saveDB();
	return 0;
}

//handle cookies and logged in users

// (username, password)
int cli_loginAsUser(char** args){
    initDB();
    initCookieDB();

    cookie c;
    if(loginAsUser(args[0], args[1], &c) < 0){
        return -1;
    }
    //output cookie info
    printf("token:\t%d\nexpiry:\t%d\n", c.token, c.expiry);

	return 0;
}

int cli_logout(char** args){
    initDB();
    logout(args[0]);
    saveDB();
	return 0;
}

//no input  //_string
int cli_getLoggedInUsers(char** args){
    return 0;
}

int cli_validateToken(char** args){
	return 0;
}


//read-only funcs
// no input
int cli_printDB(char** args){
    initDB();
	printDB();
    return 0;
}
//no input
int cli_printCookieDB(char** args){
    initCookieDB();
    printCookieDB();
    return 0;
}

int cli_printUser(char** args){
	return 0;
}

int cli_printCookie(char** args){
	return 0;
}


int cli_getUsername(char** args){
	return 0;
}


int cli_findCookieByUserID(char** args){
	return 0;
}
