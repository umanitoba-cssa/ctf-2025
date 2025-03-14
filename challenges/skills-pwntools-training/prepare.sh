#!/usr/bin/env bash

cd docker
docker build -t skills-pwntools-training -t skills-pwntools-training:latest -t git.ctf.umanitobacssa.ca/cssa/skills-pwntools-training:latest .
docker compose up -d
docker compose down

cd ..

echo "The docker container has been built and is ready to be deployed."
echo "Run test.sh to verify the challenge is working as expected."
echo "Files for the participants have been produced in the files/ directory. Please upload these files to CTFd."