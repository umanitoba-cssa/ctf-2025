#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-flakey-file-server -t web-flakey-file-server:latest -t git.ctf.umanitobacssa.ca/cssa/web-flakey-file-server:latest .
docker image push git.ctf.umanitobacssa.ca/cssa/web-flakey-file-server:latest

cd ..