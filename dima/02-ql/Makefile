BOOST=../../../boost_1_51_0
QUANTLIB_H=../../../QuantLib-1.2.1
QUANTLIB_LIB=../../../QuantLib-1.2.1/ql/.libs

macros.exe: 01-macros.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

clean:
	rm -f *.exe
