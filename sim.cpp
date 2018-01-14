//
// Created by zpltys on 2018/1/4.
//
#include "blogel_sim.h"
int main(int argc, char* argv[])
{
    init_workers();
    blogel_app_sim("/pullgel/test/", "/exp/sssp");
    worker_finalize();
    return 0;
}
