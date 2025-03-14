#!/usr/bin/env bash

make clean
make

cd docker
docker build -t web-whispers-in-the-veil -t web-whispers-in-the-veil:latest -t git.ctf.umanitobacssa.ca/cssa/web-whispers-in-the-veil:latest .
docker image push git.ctf.umanitobacssa.ca/cssa/web-whispers-in-the-veil:latest

cd ..