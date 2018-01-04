#include "blogel/Voronoi.h"
#include <iostream>
#include <sstream>
#include "blogel/BGlobal.h"
using namespace std;

class vorPart : public BPartWorker {
    char buf[1000];

public:
    // id nodeType num v1 v2 ... vn
    virtual BPartVertex* toVertex(char* line)
    {
        char* pch;
        BPartVertex* v = new BPartVertex;
        pch = strtok(line, " ");
        v->id = atoi(pch);
        pch = strtok(NULL, " ");
        v->value().nodeType = atoi(pch);
        pch = strtok(NULL, " ");
        int num = atoi(pch);

        while (num --) {
            pch = strtok(NULL, " ");
            int nb = atoi(pch);
            v->value().neighbors.push_back(nb);
        }
        return v;
    }

    virtual void toline(BPartVertex* v, BufferedWriter& writer) //key: "vertexID blockID slaveID"
    { //val: list of "vid block slave "
        sprintf(buf, "%d %d %d\t", v->id, v->value().color, _my_rank);
        writer.write(buf);

        vector<triplet>& vec = v->value().nbsInfo;
        hash_map<int, triplet> map;
        for (int i = 0; i < vec.size(); i++) {
            map[vec[i].vid] = vec[i];
        }

        int num = v->value().neighbors.size();
        for (int i = 0; i < num; i++) {
            int vid = v->value().neighbors[i];
            triplet trip = map[vid];
            sprintf(buf, "%d %d %d ", vid, trip.bid, trip.wid);
            writer.write(buf);
        }
        writer.write("\n");
    }
};

int blogel_sssp_vorPart(string in_path, string out_path)
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
