DIR_LEVEL=2
include ../../lib_path.mk

qlpch.gch: qlpch.h
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $@

integration.exe: 01-integration.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

solvers.exe: 02-solvers.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

interpolation.exe: 03-interpolation.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

matrices.exe: 04-matrices.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

optimization.exe: 05-optimization.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

rng.exe: 06-rng.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

copulas.exe: 07-copulas.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

indexes.exe: 08-indexes.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

intrates.exe: 09-intrates.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

yieldcurves.exe: 10-yieldcurves.cpp qlpch.gch
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 
