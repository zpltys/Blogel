#include "blogel_app_hashmin.h"
#include <time.h>

int main(int argc, char* argv[])
{
    init_workers();
    long start = time(NULL);
    blogel_app_hashmin("/vor/friend/", "/exp/cc");
    long end = time(NULL);
    cout << "total cc cost time:" << end - start << "s" << endl;
    worker_finalize();
    return 0;
}
