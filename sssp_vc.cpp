#include "pregel_app_sssp.h"

int main(int argc, char* argv[]){
	init_workers();
	pregel_sssp(2, "/pullgel/friend/", "/exp/sssp", true);
	worker_finalize();
	return 0;
}
