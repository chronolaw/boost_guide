TARGETS = clamp foreach hex minmax_element minmax
EXES=$(foreach d, $(TARGETS), $d.exe)

CXXFLAGS+=-std=c++11 -g -Wall 
INC=/usr/include /usr/local/include/boost
INC_PARAMS=$(foreach d, $(INC), -I$d)

LDLIBS+=
LIB=


# C++ 'compile' command:
CPP = g++ ${CXXFLAGS} ${LIB} ${INC_PARAMS} -o $@ $< ${LDLIBS}

all : ${TARGETS}

.cpp:
	${CPP}

clean:
	-rm -f *.o *.exe