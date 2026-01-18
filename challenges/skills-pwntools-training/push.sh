#!/usr/bin/env bash

make clean
make

cd docker
docker build -t skills-pwntools-training -t skills-pwntools-training:latest -t ghcr.io/umanitoba-cssa/skills-pwntools-training:latest .
docker image push ghcr.io/umanitoba-cssa/skills-pwntools-training:latest

cd ..