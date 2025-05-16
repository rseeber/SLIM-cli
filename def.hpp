#include <map>
#include <vector>

#include "funcs.hpp"
typedef int(*functionPointer)(char**);

map<string, functionPointer> options 
{
    {"addUser", &cli_addUser},
    {"editPasswd", &cli_editPasswd},
	{"editUsername", &cli_editUsername},
	{"deleteUser", &cli_deleteUser},
	{"loginAsUser", &cli_loginAsUser},
	{"logout", &cli_logout},
	{"getLoggedInUsers", &cli_getLoggedInUsers},
	{"validateToken", &cli_validateToken},
	{"printDB", &cli_printDB},
	{"printCookieDB", &cli_printCookieDB},
	{"printUser", &cli_printUser},
	{"printCookie", &cli_printCookie},
	{"getUsername", &cli_getUsername},
	{"findCookieByUserID", &cli_findCookieByUserID},
};
    
