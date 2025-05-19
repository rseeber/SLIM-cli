# this assumes that all library files are up to date before calling make
build:
	g++ main.cpp funcs.cpp lib/login.o -lcrypto -o slim