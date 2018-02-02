#!/usr/bin/env bash
rm run
rm *.log
git pull origin master
make
scp run zpltys@slave1:~/Blogel/
scp run zpltys@slave2:~/Blogel/
scp run zpltys@slave3:~/Blogel/
mpiexec -n 20 -f /home/zpltys/Blogel/conf /home/zpltys/Blogel/run
