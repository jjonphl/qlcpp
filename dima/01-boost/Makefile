DIR_LEVEL=2
include ../../lib_path.mk

macros.exe: 01-macros.cpp
	g++ -I$(BOOST) $< -o $@

sharedptr.exe: 02-sharedptr.cpp
	g++ -I$(BOOST) $< -o $@

sharedptr-ex.exe: 02-sharedptr-ex.cpp
	g++ -I$(BOOST) $< -o $@

distribution.exe: 03-distribution.cpp
	g++ -I$(BOOST) $< -o $@

randnum.exe: 04-randnum.cpp
	g++ -I$(BOOST) $< -o $@

randnum-ex.exe: 04-randnum-ex.cpp
	g++ -I$(BOOST) $< -o $@

function.exe: 05-function.cpp
	g++ -I$(BOOST) $< -o $@

clean:
	rm -f *.o *.exe
