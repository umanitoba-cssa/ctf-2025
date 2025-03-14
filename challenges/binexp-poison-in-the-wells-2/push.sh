#!/usr/bin/env bash

make clean
make

cd docker
docker build -t binexp-poison-in-the-wells-2 -t binexp-poison-in-the-wells-2:latest -t git.ctf.umanitobacssa.ca/cssa/binexp-poison-in-the-wells-2:latest .
docker image push git.ctf.umanitobacssa.ca/cssa/binexp-poison-in-the-wells-2:latest

cd ..