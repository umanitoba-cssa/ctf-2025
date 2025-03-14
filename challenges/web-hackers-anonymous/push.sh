#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-hackers-anonymous -t web-hackers-anonymous:latest -t git.ctf.umanitobacssa.ca/cssa/web-hackers-anonymous:latest .
docker image push git.ctf.umanitobacssa.ca/cssa/web-hackers-anonymous:latest

cd ..