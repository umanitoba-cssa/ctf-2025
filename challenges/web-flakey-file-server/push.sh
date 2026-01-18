#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-flakey-file-server -t web-flakey-file-server:latest -t ghcr.io/umanitoba-cssa/ctf-2025/web-flakey-file-server:latest .
docker image push ghcr.io/umanitoba-cssa/ctf-2025/web-flakey-file-server:latest

cd ..