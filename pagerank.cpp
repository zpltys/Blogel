#include "blogel_app_pagerank1.h"
#include <time.h>
int main(int argc, char* argv[])
{
    init_workers();

    long start = time(NULL);
    blogel_app_pagerank1("/vor/friend/","/exp/pr1");
    long end = time(NULL);
    cout << "total pr cost time:" << end - start << "s" << endl;

    worker_finalize();
    return 0;
}
