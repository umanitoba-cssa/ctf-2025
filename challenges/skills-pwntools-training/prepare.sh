#!/usr/bin/env bash

cd docker
docker compose up --build -d
docker compose down

cd ..

echo "The docker container has been built and is ready to be deployed."
echo "Run test.sh to verify the challenge is working as expected."
echo "Files for the participants have been produced in the files/ directory. Please upload these files to CTFd."