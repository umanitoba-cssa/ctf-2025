#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-hackers-anonymous -t web-hackers-anonymous:latest -t ghcr.io/umanitoba-cssa/ctf-2025/web-hackers-anonymous:latest .
docker image push ghcr.io/umanitoba-cssa/ctf-2025/web-hackers-anonymous:latest

cd ..