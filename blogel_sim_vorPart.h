#include "blogel/Voronoi.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "blogel/BGlobal.h"
using namespace std;
const int mod = 10;
class vorPart : public BPartWorker {
    char buf[1000];

public:

    virtual BPartVertex* toVertex(char* line)
    {
      /*char* pch;
        BPartVertex* v = new BPartVertex;
        v->value().content = line; //first set content!!! line will change later due to "strtok"
        pch = strtok(line, " ");
        v->id = atoi(pch);

        pch = strtok(NULL, " ");
        int num = atoi(pch);

        while (num --) {
            pch = strtok(NULL, " ");
            int nb = atoi(pch);
            v->value().neighbors.push_back(nb);
        }
        return v;
        */

        char* pch;
        BPartVertex* v = new BPartVertex;
        v->value().content = line; //first set content!!! line will change later due to "strtok"
        pch = strtok(line, "\t");
        v->id = atoi(pch);


        while (true) {
            pch = strtok(NULL, " ");
            if (pch == NULL) break;
            int nb = atoi(pch);
            v->value().neighbors.push_back(nb);
        }
        if (v->id < 10) {
            printf("id: %d,  edges:", v->id);
            for(int i = 0; i < v->value().neighbors.size(); i++) {
                printf(" %d", v->value().neighbors[i]);
            }
            printf("\n");
        }
        return v;
    }

    virtual void toline(BPartVertex* v, BufferedWriter& writer) //key: "vertexID blockID slaveID"
    { //val: list of "vid block slave "
        sprintf(buf, "%d %d %d %d ", v->id, v->id % mod, v->value().color, _my_rank);
        writer.write(buf);

        vector<triplet>& vec = v->value().nbsInfo;
        hash_map<int, triplet> map;
        for (int i = 0; i < vec.size(); i++) {
            map[vec[i].vid] = vec[i];
        }
        ////////
        stringstream ss(v->value().content);
        string token;
        ss >> token; //vid
  //      ss >> token; //number    for webbase
        int num = v->value().neighbors.size();
        sprintf(buf, "%d ", num);
        writer.write(buf);
        for (int i = 0; i < num; i++) {
            ss >> token;
            int vid = atoi(token.c_str());
            triplet trip = map[vid];
            sprintf(buf, "%d %d %d ", vid, trip.bid, trip.wid);
            writer.write(buf);
        }
        writer.write("\n");
    }
};

int blogel_sim_vorPart(string in_path, string out_path)
{
    WorkerParams param;
    param.input_path = in_path;
    param.output_path = out_path;
    param.force_write = true;
    param.native_dispatcher = false;
    bool to_undirected = false;
    //////
    set_sampRate(0.01);
    set_maxHop(50);
    set_maxVCSize(1000000000);
    set_factor(2);
    set_stopRatio(0.9);
    set_maxRate(0.1);
    //////
    vorPart worker;
    worker.run(param, to_undirected);
}
