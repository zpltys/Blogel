CCOMPILE=mpic++
PLATFORM=Linux-amd64-64
CPPFLAGS= -I$(HADOOP_HOME)/src/c++/libhdfs -L$(JAVA_HOME)/jre/lib/amd64/server -I$(JAVA_HOME)/include/linux -I$(JAVA_HOME)/include -I /home/zpltys/blogel
LIB = -L/home/zhangshuai/hadoop-1.2.1/c++/Linux-amd64-64/lib
LDFLAGS = -lhdfs -ljvm -Wno-deprecated -O2

all: part sssp cc

part: sim_part.cpp
	$(CCOMPILE) sim_part.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o part

cc: cc.cpp
	$(CCOMPILE) cc.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o cc

pr: pagerank.cpp
    $(CCOMPILE) pagerank.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o pr

put: put.cpp
    $(CCOMPILE) put.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o put

clean:
    -rm cc part pr put
