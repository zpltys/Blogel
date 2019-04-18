CCOMPILE=mpic++
PLATFORM=Linux-amd64-64
CPPFLAGS= -I$(HADOOP_HOME)/src/c++/libhdfs -I$(JAVA_HOME)/jre/lib/amd64/server -I$(JAVA_HOME)/include/linux -I$(JAVA_HOME)/include -I /home/zpltys/blogel
LIB = -L/home/zhangshuai/hadoop-1.2.1/c++/Linux-amd64-64/lib
LDFLAGS = -lhdfs -Wno-deprecated -O2

all: cc part pr

part: pagerank_part.cpp
	$(CCOMPILE) pagerank_part.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o part

cc: cc.cpp
	$(CCOMPILE) cc.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o cc

pr: pagerank.cpp
	$(CCOMPILE) pagerank.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o pr

clean:
	-rm cc part pr
