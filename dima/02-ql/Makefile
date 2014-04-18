DIR_LEVEL=2
include ../../lib_path.mk

macros.exe: 01-macros.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

vartypes.exe: 02-vartypes.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

dates.exe: 03-dates.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

calendars.exe: 04-calendars.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

daycounts.exe: 05-daycounts.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

schedules.exe: 06-schedules.cpp
	g++ -c -Wall -I${BOOST} -I${QUANTLIB_H} $< -o $(patsubst %.exe,%.o,$@)
	g++ -L${QUANTLIB_LIB} $(patsubst %.exe,%.o,$@) -o $@ -lQuantLib 

clean:
	rm -f *.exe
