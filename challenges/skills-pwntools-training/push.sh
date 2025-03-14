#!/usr/bin/env bash

make clean
make

cd docker
docker build -t skills-pwntools-training -t skills-pwntools-training:latest -t git.ctf.umanitobacssa.ca/cssa/skills-pwntools-training:latest .
docker image push git.ctf.umanitobacssa.ca/cssa/skills-pwntools-training:latest

cd ..