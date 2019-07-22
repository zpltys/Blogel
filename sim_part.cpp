#include "blogel_sim_vorPart.h"

int main(int argc, char* argv[])
{
    init_workers();
    blogel_sim_vorPart("/pullgel/webbase/", "/vor/webbase");
    worker_finalize();
    return 0;

}
