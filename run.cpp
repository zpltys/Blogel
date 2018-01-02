#include "blogel_sssp_STRRnd1.h"
#include "blogel_sssp_STRRnd2.h"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "initial start" << std::endl;
    init_workers();
    std::cout << "end initial" << std::endl;
    blogel_sssp_STRRnd1("/pullgel/test", "/str1/usaxy_1");
    std::cout << "sssp STRRND1 end" << std::endl;
    blogel_sssp_STRRnd2("/str1/usaxy_1", "/str1/usaxy_2");
    worker_finalize();
    return 0;
}
