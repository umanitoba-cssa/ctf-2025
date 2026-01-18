#!/usr/bin/env bash

make clean
make

cd docker
# Use parent dir as build context so Dockerfile can COPY bin/
docker build -f Dockerfile -t binexp-poison-in-the-wells-4 -t binexp-poison-in-the-wells-4:latest -t ghcr.io/umanitoba-cssa/ctf-2025/binexp-poison-in-the-wells-4:latest ..
docker image push ghcr.io/umanitoba-cssa/ctf-2025/binexp-poison-in-the-wells-4:latest

cd ..