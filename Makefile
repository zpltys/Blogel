CCOMPILE=mpic++
PLATFORM=Linux-amd64-64
CPPFLAGS= -I$(HADOOP_HOME)/src/c++/libhdfs -L$(JAVA_HOME)/jre/lib/amd64/server -I$(JAVA_HOME)/include/linux -I$(JAVA_HOME)/include -I /home/zpltys/blogel
LIB = -L/home/zhangshuai/hadoop-1.2.1/c++/Linux-amd64-64/lib
LDFLAGS = -lhdfs -ljvm -Wno-deprecated -O2

all: part sssp

part: sssp_part.cpp
	$(CCOMPILE) sssp_part.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o part

sssp: sssp.cpp
	$(CCOMPILE) sssp.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o sssp

clean:
	-rm part sssp
