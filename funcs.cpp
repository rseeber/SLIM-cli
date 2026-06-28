#include <iostream>
#include <stdio.h>
#include <cstring>
//#include <stdint.h>
#include <sstream>
#include <cstdint>
#include "lib/login.hpp"
using namespace std;


//modify DB

// (username, password) creates a user as specified, adding them to the DB
int cli_addUser(int argc, char** argv){
    initDB();
    //don't use emails that's stupid we don't need them
    int flag = addUser(argv[0], argv[1]);
    saveDB();
    return flag;
}

// input username and newPass. Updates the user's info if they exist.
// NOTE: Library imlimentation is broken currently
int cli_editPasswd(int argc, char** argv){
    initDB();

    login l;
    if(findUserByName(argv[0], &l) < 0){
        return -1;
    }

    editPasswd(l.userID, argv[1]);
    saveDB();
    return 0;
}

// input username and newUsername. Updates the user's info if they exist.
// NOTE: Library imlimentation is broken currently
int cli_editUsername(int argc, char** argv){
    initDB();

    login l;
    if(findUserByName(argv[0], &l) < 0){
        return -1;
    }
    printf("username pre-edit: %s\n", l.user);

    if(editUsername(l.userID, argv[1]) < 0){
        return -1;
    }

    printf("username post-edit: %s\n", l.user);
    saveDB();
	return 0;
}

// (username) self explanatory
int cli_deleteUser(int argc, char** argv){
    initDB();
    login l;
    if(findUserByName(argv[0], &l) < 0){
        return -1;
    }
    // revoke the cookie
    logout(l.user);
    // then delete their account
    deleteUser(l.userID);
    saveDB();
	return 0;
}

//handle cookies and logged in users

// (username, password)
int cli_loginAsUser(int argc, char** argv){
    initDB();
    initCookieDB();

    cookie c;
    if(loginAsUser(argv[0], argv[1], &c) < 0){
        return -1;
    }
    //output cookie info
    //printf("token:\t%" PRIu64 "\nexpiry:\t%d\n", c.token, c.expiry);
    cout << "token:\t" << c.token << "\nexpiry:\t" << c.expiry << endl;

    //save the cookie database
    saveCookieDB();

	return 0;
}

int cli_logout(int argc, char** argv){
    initDB();
    logout(argv[0]);
    saveDB();
	return 0;
}


//read-only funcs
//no input  //_string
int cli_getLoggedInUsers(int argc, char** argv){
    initDB();
    initCookieDB();
    // get the list
    list<login> logins = getLoggedInUsers();
    // loop through and print it all
    list<login>::iterator it;
    // For human readability
    bool human = (argc > 0 && strcmp(argv[0], "-h") == 0);
    if(human){
        cout << "  Username\t|   UserID\t|\t\t\tPassword Hash\t\t\t\t   |\t\tPassword Salt" << endl;
        for(int i = 0; i < 133; ++i){
            cout << "-";
        }
        cout << endl;
    }
    for(it = logins.begin(); it != logins.end(); ++it){
        // print the data as a nice table for humans
        if(human){
            cout << it->user;
            if (it->user.length() < 8){
                cout << "\t";
            }
            cout << "\t| " << it->userID << "\t| " << it->passHash << " | " << it->salt << endl;
        }
        // just print it tab and newline seperated
        else{
            // username, userID, password hash, password salt
            cout << it->user << "\t" << it->userID << "\t" << it->passHash << "\t" << it->salt << endl;
        }
    }
    return 0;
}

int cli_validateToken(int argc, char** argv){
    initDB();
    initCookieDB();
    // convert our cli argument into an int
    uint64_t token;
    istringstream iss(argv[0]);
    iss >> token;
    
    // pass the token in, getting our userID for that cookie
    int userID = validateToken(token);
    // get username and email for that user
    login l;
    if (findUserByID(userID, &l) < 0){
        cout << "Can't find user" << endl;
        return -1;
    }
	return 0;
}

// no input
int cli_printDB(int argc, char** argv){
    initDB();
	printDB();
    return 0;
}
//no input
int cli_printCookieDB(int argc, char** argv){
    initCookieDB();
    printCookieDB();
    return 0;
}

int cli_printUser(int argc, char** argv){
	return 0;
}

int cli_printCookie(int argc, char** argv){
	return 0;
}


int cli_getUsername(int argc, char** argv){
	return 0;
}


int cli_findCookieByUserID(int argc, char** argv){
	return 0;
}
