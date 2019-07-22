//
// Created by zpltys on 2018/1/4.
//
#ifndef BLOGEL_BLOGEL_SIM_H
#define BLOGEL_BLOGEL_SIM_H

#include "utils/Combiner.h"
#include "blogel/BVertex.h"
#include "blogel/Block.h"
#include "blogel/BWorker.h"
#include "blogel/BGlobal.h"
#include "blogel/Heap.h"

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

struct patternNode {
    int color;
    set<int> postSet;
};

map<int, patternNode> pattern;

void init_pattern() {
    pattern[1] = patternNode();
    pattern[2] = patternNode();
    pattern[3] = patternNode();
    pattern[4] = patternNode();
    pattern[5] = patternNode();
    pattern[6] = patternNode();
    pattern[7] = patternNode();
    pattern[8] = patternNode();
    pattern[1].color = 0;
    pattern[2].color = 1;
    pattern[3].color = 2;
    pattern[4].color = 3;
    pattern[5].color = 4;
    pattern[6].color = 5;
    pattern[7].color = 6;
    pattern[8].color = 7;

    pattern[1].postSet = set<int>();
    pattern[1].postSet.insert(2);
    pattern[1].postSet.insert(3);

    pattern[2].postSet = set<int>();
    pattern[2].postSet.insert(4);
    pattern[2].postSet.insert(8);

    pattern[3].postSet = set<int>();
    pattern[3].postSet.insert(4);
    pattern[3].postSet.insert(7);

    pattern[4].postSet = set<int>();
    pattern[4].postSet.insert(1);
    pattern[4].postSet.insert(8);

    pattern[5].postSet = set<int>();
    pattern[5].postSet.insert(3);
    pattern[5].postSet.insert(6);
    pattern[5].postSet.insert(8);

    pattern[6].postSet = set<int>();
    pattern[6].postSet.insert(2);
    pattern[6].postSet.insert(7);

    pattern[7].postSet = set<int>();
    pattern[7].postSet.insert(4);

    pattern[8].postSet = set<int>();
    pattern[8].postSet.insert(4);
}

struct SimEdge
{
    int nv;
    int block;
    int worker;
};

//====================================
// u is pattern id, while v is data graph id
typedef map<int, int> SimMsg;

struct SimValue
{
    int color;
    set<int> sim;
    map<int, int> postMap;
    vector<SimEdge> preEdges;
    SimMsg messageBuffer;
    int split; //v.edges[0, ..., inSplit] are local to block
};


class SimVertex : public BVertex<VertexID, SimValue, SimMsg>
{
public:
    virtual void compute(MessageContainer& messages)
    {
        if (step_num() == 1) {
            for (map<int, patternNode>::iterator it = pattern.begin(); it != pattern.end(); it++) {
                int u = it->first;
                patternNode node = it->second;
                if (node.color == value().color) {
                    value().messageBuffer[u] += 1;
                    value().sim.insert(u);
                }
            }
        } else {
            if (step_num() == 2) {
                for (int i = 0; i < messages.size(); i++) {
                    SimMsg& msg = messages[i];
                    for (SimMsg::iterator it = msg.begin(); it != msg.end(); it++) {
                        value().postMap[it->first] += it->second;
                    }
                }
            } else {
                for (int i = 0; i < messages.size(); i++) {
                    SimMsg& msg = messages[i];
                    for (SimMsg::iterator it = msg.begin(); it != msg.end(); it++) {
                        value().postMap[it->first] -= it->second;
                    }
                }
            }

            vector<int> deleted;
            for (set<int>::iterator it = value().sim.begin(); it != value().sim.end(); it++) {
                int u = *it;
                bool match = true;
                for (set<int>::iterator temp = pattern[u].postSet.begin(); temp != pattern[u].postSet.end(); temp++) {
                    int v = *temp;
                    if (value().postMap[v] == 0) {
                        match = false;
                        break;
                    }
                }

                if (!match) {
                    deleted.push_back(u);
                }
            }
            value().messageBuffer.clear();
            for (int i = 0; i < deleted.size(); i++) {
                value().messageBuffer[deleted[i]] = 1;
                value().sim.erase(deleted[i]);
            }
            if (deleted.empty()) vote_to_halt();
        }
    }
};

//====================================

class SimBlock : public Block<char, SimVertex, char>
{
public:
    virtual void compute(MessageContainer& messages, VertexContainer& vertexes) //multi-source Dijkstra (assume a super src node)
    { //heap is better than queue, since each vertex is enheaped only once
        //collect active seeds

        queue<SimVertex*> q;
        map<int, bool> inQueue;
        for (int i = begin; i < begin + size; i++) {
            SimVertex& vertex = *vertexes[i];
            if (!vertex.is_active()) continue;

            q.push(&vertex);
            inQueue[vertex.id] = true;
            vertex.vote_to_halt();
        }
        if (step_num() >= 2) {
            while (!q.empty()) {
                SimVertex &vertex = *q.front();
                q.pop();
                inQueue[vertex.id] = false;

                vector<int> deleted;
                for (set<int>::iterator it = vertex.value().sim.begin(); it != vertex.value().sim.end(); it++) {
                    int u = *it;
                    bool match = true;
                    for (set<int>::iterator temp = pattern[u].postSet.begin();
                         temp != pattern[u].postSet.end(); temp++) {
                        int v = *temp;
                        if (vertex.value().postMap[v] == 0) {
                            match = false;
                            break;
                        }
                    }

                    if (!match) {
                        deleted.push_back(u);
                    }
                }
                for (int i = 0; i < deleted.size(); i++) {
                    vertex.value().messageBuffer[deleted[i]] = 1;
                    vertex.value().sim.erase(deleted[i]);
                }
                if (vertex.value().messageBuffer.empty()) continue;

                SimValue &value = vertex.value();
                for (int i = 0; i <= value.split; i++) {
                    int nvId = value.preEdges[i].worker;
                    SimVertex &uVertex = *vertexes[nvId];

                    for (map<int, int>::iterator it = value.messageBuffer.begin(); it != value.messageBuffer.end(); it++) {
                        uVertex.value().postMap[it->first]--;
                    }
                    if (!inQueue[uVertex.id]) {
                        inQueue[uVertex.id] = true;
                        q.push(&uVertex);
                    }
                }

                for (int i = value.split + 1; i < value.preEdges.size(); i++) {
                    SimEdge &e = value.preEdges[i];
                    vertex.send_message(e.nv, e.worker, value.messageBuffer);
                }
                value.messageBuffer.clear();
            }
        } else {
            while (!q.empty()) {
                SimVertex &vertex = *q.front();
                q.pop();
                inQueue[vertex.id] = false;
                SimValue &value = vertex.value();

                for (int i = 0; i <= value.split; i++) {
                    int nvId = value.preEdges[i].worker;
                    SimVertex &uVertex = *vertexes[nvId];

                    for (map<int, int>::iterator it = value.messageBuffer.begin(); it != value.messageBuffer.end(); it++) {
                        uVertex.value().postMap[it->first] += it->second;
                    }
                }

                for (int i = value.split + 1; i < value.preEdges.size(); i++) {
                    SimEdge &e = value.preEdges[i];
                    vertex.send_message(e.nv, e.worker, value.messageBuffer);
                }
                value.messageBuffer.clear();
            }
        }
        inQueue.clear();
        vote_to_halt();
    }
};

//====================================

class SPBlockWorker : public BWorker<SimBlock> {
    char buf[1000];

public:
    virtual void blockInit(VertexContainer &vertexes, BlockContainer &blocks) {
        hash_map<int, int> mp;
        for (int i = 0; i < vertexes.size(); i++)
            mp[vertexes[i]->id] = i;
        //////
        if (_my_rank == MASTER_RANK)
            cout << "Splitting in/out-block edges ..." << endl;
        for (BlockIter it = blocks.begin(); it != blocks.end(); it++) {
            SimBlock *block = *it;
            for (int i = block->begin; i < block->begin + block->size; i++) {
                SimVertex *vertex = vertexes[i];
                vector<SimEdge> &edges = vertex->value().preEdges;
                vector<SimEdge> tmp;
                vector<SimEdge> tmp1;
                for (int j = 0; j < edges.size(); j++) {
                    if (edges[j].block == block->bid) {
                        edges[j].worker = mp[edges[j].nv]; //workerID->array index
                        tmp.push_back(edges[j]);
                    } else
                        tmp1.push_back(edges[j]);
                }
                edges.swap(tmp);
                vertex->value().split = edges.size() - 1;
                edges.insert(edges.end(), tmp1.begin(), tmp1.end());
            }
        }
        if (_my_rank == MASTER_RANK) {
            cout << "In/out-block edges split" << endl;
        }
    }

    //input line format: vid blockID workerID \t nb1 nb2 ...
    //nbi format: vid edgeLength blockID workerID
    virtual SimVertex *toVertex(char *line) {
        char *pch;
        pch = strtok(line, " ");
        SimVertex *v = new SimVertex;
        v->id = atoi(pch);
        pch = strtok(NULL, " ");
        v->value().color = atoi(pch);
        pch = strtok(NULL, " ");
        v->bid = atoi(pch);
        pch = strtok(NULL, " ");
        v->wid = atoi(pch);
        vector<SimEdge> &edges = v->value().preEdges;
        pch = strtok(NULL, " ");
        int num = atoi(pch);
        while (num--) {
            SimEdge trip;
            pch = strtok(NULL, " ");
            trip.nv = atoi(pch);
            pch = strtok(NULL, " ");
            trip.block = atoi(pch);
            pch = strtok(NULL, " ");
            trip.worker = atoi(pch);
            edges.push_back(trip);
        }
        ////////
        if (edges.empty()) v->vote_to_halt();

        return v;
    }

    virtual void toline(SimBlock *b, SimVertex *v, BufferedWriter &writer) {
        if (!v->value().sim.empty()) {
            sprintf(buf, "%d\t", v->id);
            writer.write(buf);
            for (set<int>::iterator it = v->value().sim.begin(); it != v->value().sim.end(); it++) {
                sprintf(buf, "%d ", *it);
                writer.write(buf);
            }
            sprintf(buf, "\n");
            writer.write(buf);
        }
    }
};

class SPCombiner : public Combiner<SimMsg>
{
public:
    virtual void combine(SimMsg& old, const SimMsg& new_msg)
    {
        for (map<int, int>::const_iterator it = new_msg.begin(); it != new_msg.end(); it++) {
            old[it->first] += it->second;
        }
    }
};

void blogel_app_sim(string in_path, string out_path)
{
    WorkerParams param;
    param.input_path = in_path;
    param.output_path = out_path;
    param.force_write = true;
    SPBlockWorker worker;
    worker.set_compute_mode(SPBlockWorker::VB_COMP);
    init_pattern();
    SPCombiner combiner;
    worker.setCombiner(&combiner);
    worker.run(param);
}

#endif //BLOGEL_BLOGEL_SIM_H
