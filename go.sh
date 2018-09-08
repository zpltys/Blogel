#!/usr/bin/env bash
rm run
rm *.log
make
scp run zpltys@slave1:~/Blogel/
scp run zpltys@slave2:~/Blogel/
scp run zpltys@slave3:~/Blogel/
mpiexec -n 24 -f /home/zpltys/Blogel/conf24 /home/zpltys/Blogel/run
