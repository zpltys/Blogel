//
// Created by zpltys on 2018/1/4.
//
#include "blogel_sim.h"
#include <time.h>
int main(int argc, char* argv[])
{

    long start = time(NULL);
    init_workers();
    blogel_app_sim("/vor/webbase/", "/exp/sim");
    worker_finalize();
    long end = time(NULL);
    cout << "total sim cost time:" << end - start << "s" << endl;
    return 0;
}
