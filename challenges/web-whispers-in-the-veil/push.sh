#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-whispers-in-the-veil -t web-whispers-in-the-veil:latest -t ghcr.io/umanitoba-cssa/ctf-2025/web-whispers-in-the-veil:latest .
docker image push ghcr.io/umanitoba-cssa/ctf-2025/web-whispers-in-the-veil:latest

cd ..