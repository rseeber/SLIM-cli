using namespace std;


//modify DB
int cli_addUser(int argc, char** argv);

int cli_editPasswd(int argc, char** argv);
int cli_editUsername(int argc, char** argv);

int cli_deleteUser(int argc, char** argv);

//handle cookies and logged in users
int cli_loginAsUser(int argc, char** argv);

int cli_logout(int argc, char** argv);
int cli_logout(int argc, char** argv);

int cli_getLoggedInUsers(int argc, char** argv); //no input  //_string

int cli_validateToken(int argc, char** argv);


//read-only funcs
int cli_printDB(int argc, char** argv); // no input
int cli_printCookieDB(int argc, char** argv); //no input

int cli_printUser(int argc, char** argv);
int cli_printUser(int argc, char** argv);

int cli_printCookie(int argc, char** argv);
int cli_printCookie(int argc, char** argv);


int cli_getUsername(int argc, char** argv);
//int cli_findUserByName();
//int cli_findUserByID();


int cli_findCookieByUserID(int argc, char** argv);
