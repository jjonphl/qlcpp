BOOST=../../boost_1_51_0
QUANTLIB_H=../../QuantLib-1.4
QUANTLIB_LIB=../../ql-1.4

bonds.exe: Bonds.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

swapvaluation.exe: swapvaluation.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} -I. $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

clean:
	rm -f *.exe
