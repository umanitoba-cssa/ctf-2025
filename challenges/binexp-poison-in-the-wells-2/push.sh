#!/usr/bin/env bash

make clean
make

cd docker
docker build -f Dockerfile -t binexp-poison-in-the-wells-2 -t binexp-poison-in-the-wells-2:latest -t ghcr.io/umanitoba-cssa/ctf-2025/binexp-poison-in-the-wells-2:latest ..
docker image push ghcr.io/umanitoba-cssa/ctf-2025/binexp-poison-in-the-wells-2:latest

cd ..