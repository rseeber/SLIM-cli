# SLIM-CLI
This project is a simple cli wrapper for the SLIM C++ library (https://github.com/rseeber/SLIM). The interface uses a simple, stateless API, which does not rely on any daemon or service.

# Commands

## addUser
`slim addUser <username> <email> <plaintext password>`

creates user with the specified login details, and adds them to the users file.

## editUser
`slim editUser <option> <new value>`

options: `username`, `password`, `email`

## login
`slim login <username> <plaintext password>`

attempts to log the specified user in. On success, they will have a unique cookie
created for them and added to the cookies file. On failure, it will return an error.

## logout
`slim logout <userID>`

logs the specified user out, removing their token from the cookies file. 

Note: If you do not manually log a user out, their token will automatically expire
after 10 minutes, and they will be logged out.

## deleteUser
`slim deleteUser <userID>`

## verifyToken
`slim verifyToken <token>`

If the cookie is unexpired, it returns the userID associated with the token. If the cookie
is expired, or if no such token exists, returns -1. (userID's are always positive).

## *findUser
`slim findUser <byType> <identifier>`

byType: `byID`, `byName`.

the identifier is either the userID or the username. It prints out that user's info. Returns -1 on lookup error.

# *findCookie
`slim findCookie <byType> <identifier>`

byType: `byID`, `byName`.

same as `slim findUser`, except it queries for *unexpired* cookies in the cookie file. Prints the info for the cookie, not necessarily all data for the given user.

## *help
`slim help` 

returns a list of possible commands