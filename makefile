build:lib
	g++ main.cpp funcs.cpp lib/login.o -lcrypto -o slim

lib:clean
	# tells the makefile in SLIM/ to run the lib recipe
	$(MAKE) -C SLIM lib
	mv SLIM/bin lib

clean:
	gio trash lib/ -f

full:clean lib build
	