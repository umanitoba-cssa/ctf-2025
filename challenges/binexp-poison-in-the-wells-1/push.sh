#!/usr/bin/env bash

make clean
make

cd docker
docker build -f Dockerfile -t binexp-poison-in-the-wells-1 -t binexp-poison-in-the-wells-1:latest -t ghcr.io/umanitoba-cssa/ctf-2025/binexp-poison-in-the-wells-1:latest ..
docker image push ghcr.io/umanitoba-cssa/ctf-2025/binexp-poison-in-the-wells-1:latest

cd ..