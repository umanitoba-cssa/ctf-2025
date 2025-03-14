#!/usr/bin/env bash

cd docker
docker build -t web-flakey-file-server -t web-flakey-file-server:latest -t git.ctf.umanitobacssa.ca/cssa/web-flakey-file-server:latest .
docker compose up -d
docker compose down

cd ..

echo "The docker container has been built and pushed and is ready to be deployed."