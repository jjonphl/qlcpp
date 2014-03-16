BOOST_PATH=../../../boost_1_51_0

macros.exe: 01-macros.cpp
	g++ -I$(BOOST_PATH) $< -o $@

sharedptr.exe: 02-sharedptr.cpp
	g++ -I$(BOOST_PATH) $< -o $@

sharedptr-ex.exe: 02-sharedptr-ex.cpp
	g++ -I$(BOOST_PATH) $< -o $@

distribution.exe: 03-distribution.cpp
	g++ -I$(BOOST_PATH) $< -o $@

randnum.exe: 04-randnum.cpp
	g++ -I$(BOOST_PATH) $< -o $@

randnum-ex.exe: 04-randnum-ex.cpp
	g++ -I$(BOOST_PATH) $< -o $@

function.exe: 05-function.cpp
	g++ -I$(BOOST_PATH) $< -o $@

clean:
	rm -f *.exe
