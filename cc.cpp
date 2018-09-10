#include "blogel_app_hashmin.h"

int main(int argc, char* argv[])
{
    init_workers();
    long start = time(NULL);
    blogel_app_hashmin("/vor/liveJournal", "/exp/cc");
    long end = time(NULL);
    cout << "total cost time:" << end - start << "s" << endl;
    worker_finalize();
    return 0;
}
