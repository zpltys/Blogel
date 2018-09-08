#!/usr/bin/env bash
scp run zpltys@slave1:~/Blogel/
scp run zpltys@slave2:~/Blogel/
scp run zpltys@slave3:~/Blogel/
scp part zpltys@slave1:~/Blogel/
scp part zpltys@slave2:~/Blogel/
scp part zpltys@slave3:~/Blogel/
mpiexec -n 24 -f /home/zpltys/Blogel/conf24 /home/zpltys/Blogel/part 2> usaroad.part.24.log
mpiexec -n 24 -f /home/zpltys/Blogel/conf24 /home/zpltys/Blogel/run 2> sssp.usaroad.run.24.log
