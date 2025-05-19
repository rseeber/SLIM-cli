#include <iostream>
#include <stdio.h>
using namespace std;


//modify DB
int cli_addUser(char** argv){
    printf("calling cli_addUser()\n");
    return 0;
}

int cli_editPasswd(char** argv){
    return 0;
}
int cli_editUsername(char** argv){
	return 0;
}

int cli_deleteUser(char** argv){
	return 0;
}

//handle cookies and logged in users
int cli_loginAsUser(char** argv){
	return 0;
}

int cli_logout(char** argv){
	return 0;
}

//no input  //_string
int cli_getLoggedInUsers(char** argv){
    return 0;
}

int cli_validateToken(char** argv){
	return 0;
}


//read-only funcs
// no input
int cli_printDB(char** argv){
	return 0;
}
//no input
int cli_printCookieDB(char** argv){
    return 0;
}

int cli_printUser(char** argv){
	return 0;
}

int cli_printCookie(char** argv){
	return 0;
}


int cli_getUsername(char** argv){
	return 0;
}


int cli_findCookieByUserID(char** argv){
	return 0;
}
