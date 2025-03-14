#!/usr/bin/env bash

cd docker
docker build -t web-hackers-anonymous -t web-hackers-anonymous:latest -t git.ctf.umanitobacssa.ca/cssa/web-hackers-anonymous:latest .
docker compose up -d
docker compose down

cd ..

echo "The docker container has been built and pushed and is ready to be deployed."