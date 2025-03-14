#!/usr/bin/env bash

make clean
make

cd docker
docker build -t binexp-poison-in-the-wells-1 -t binexp-poison-in-the-wells-1:latest -t git.ctf.umanitobacssa.ca/cssa/binexp-poison-in-the-wells-1:latest .
docker image push git.ctf.umanitobacssa.ca/cssa/binexp-poison-in-the-wells-1:latest

cd ..