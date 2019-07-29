#include "blogel_sim_vorPart.h"
#include <time.h>
int main(int argc, char* argv[])
{
    long start = time(NULL);
    init_workers();
    blogel_sim_vorPart("/pullgel/twitter/", "/vor/twitter/");
    worker_finalize();
    long end = time(NULL);
    cout << "total cost time:" << end - start << "s" << endl;
    return 0;

}
