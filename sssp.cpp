#include "blogel_app_sssp.h"
#include <time.h>
int main(int argc, char* argv[])
{
    long start = time(NULL);
    init_workers();
    blogel_app_sssp("/vor/lj/", "/vor/sssp");
    worker_finalize();
    long end = time(NULL);
    cout << "total sssp cost time:" << end - start << "s" << endl;
    return 0;
}
