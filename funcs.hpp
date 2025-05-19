using namespace std;


//modify DB
int cli_addUser(char** argv);

int cli_editPasswd(char** argv);
int cli_editUsername(char** argv);

int cli_deleteUser(char** argv);

//handle cookies and logged in users
int cli_loginAsUser(char** argv);

int cli_logout(char** argv);
int cli_logout(char** argv);

int cli_getLoggedInUsers(char** argv); //no input  //_string

int cli_validateToken(char** argv);


//read-only funcs
int cli_printDB(char** argv); // no input
int cli_printCookieDB(char** argv); //no input

int cli_printUser(char** argv);
int cli_printUser(char** argv);

int cli_printCookie(char** argv);
int cli_printCookie(char** argv);


int cli_getUsername(char** argv);
//int cli_findUserByName();
//int cli_findUserByID();


int cli_findCookieByUserID(char** argv);
