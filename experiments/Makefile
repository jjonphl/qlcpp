DIR_LEVEL=1
include ../lib_path.mk

qlpch.h.gch: qlpch.h
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $@

interest_rates.exe: interest_rates.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

bonds.exe: bonds.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

