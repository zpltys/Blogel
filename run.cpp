//#include "blogel_app_pagerank1.h"
#include "blogel_app_pagerank2.h"
int main(int argc, char* argv[])
{
    init_workers();

    long start = time(NULL);
    //blogel_app_pagerank1("/vor/liveJournal","/exp/pr1");
    blogel_app_pagerank2("/vor/pr1", "/exp/pr");
    long end = time(NULL);
    cout << "total cost time:" << end - start << "s" << endl;

    worker_finalize();
    return 0;
}
