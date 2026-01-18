#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-client-sided -t web-client-sided:latest -t ghcr.io/umanitoba-cssa/ctf-2025/web-client-sided:latest .
docker image push ghcr.io/umanitoba-cssa/ctf-2025/web-client-sided:latest

cd ..