//
// Created by zpltys on 2018/1/4.
//
#include "blogel_sim.h"
#include <time.h>
int main(int argc, char* argv[])
{

    long start = time(NULL);
    init_workers();
    blogel_app_sim("/vor/liveJournal", "/exp/sim");
    worker_finalize();
    long end = time(NULL);
    cout << "total cost time:" << start - end << "s" << endl;
    return 0;
}
