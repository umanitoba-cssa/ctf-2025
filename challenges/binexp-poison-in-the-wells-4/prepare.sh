#!/usr/bin/env bash

make clean
make

cd docker
docker build -t binexp-poison-in-the-wells-4 -t binexp-poison-in-the-wells-4:latest -t ghcr.io/umanitoba-cssa/ctf-2025/binexp-poison-in-the-wells-4:latest -f docker/Dockerfile .
docker compose up -d
docker compose down

cd ..

echo "The docker container has been built and is ready to be deployed."
echo "Run test.sh to verify the challenge is working as expected."
echo "Files for the participants have been produced in the files/ directory. Please upload these files to CTFd."