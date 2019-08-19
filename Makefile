CCOMPILE=mpic++
PLATFORM=Linux-amd64-64
CPPFLAGS= -I$(HADOOP_HOME)/src/c++/libhdfs -L$(JAVA_HOME)/jre/lib/amd64/server -I$(JAVA_HOME)/include/linux -I$(JAVA_HOME)/include -I /home/zpltys/blogel
LIB = -L/home/zhangshuai/hadoop-1.2.1/c++/Linux-amd64-64/lib
LDFLAGS = -lhdfs -ljvm -Wno-deprecated -O2

all: pr sssp cc

cc: cc_vc.cpp
	$(CCOMPILE) cc_vc.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o cc

sssp: sssp_vc.cpp
	$(CCOMPILE) sssp_vc.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o sssp

pr: pr_vc.cpp
    $(CCOMPILE) pr_vc.cpp $(CPPFLAGS) $(LIB) $(LDFLAGS)  -o pr

clean:
	-rm pr sssp cc
