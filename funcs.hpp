#include <string>
using namespace std;

//modify DB
int cli_addUser(string username, string password);

int cli_editPasswd(string username, string newPassword);
int cli_editUsername(string currentUsername, string newUsername);

int cli_deleteUser(string username);

//handle cookies and logged in users
int cli_loginAsUser(string username, string password);

int cli_logout(string username);
int cli_logout(int token);

int getLoggedInUsers(); //_string

int validateToken(int token);


//read-only funcs
int printDB();
int printCookieDB();

int printUser(int token);
int printUser(string username);

int printCookie(int token);
int printCookie(string username);


int getUsername(int userID);
//int findUserByName();
//int findUserByID();


int findCookieByUserID(int userID);