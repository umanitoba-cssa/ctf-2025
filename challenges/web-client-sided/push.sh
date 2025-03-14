#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-client-sided -t web-client-sided:latest -t git.ctf.umanitobacssa.ca/cssa/web-client-sided:latest .
docker image push git.ctf.umanitobacssa.ca/cssa/web-client-sided:latest

cd ..