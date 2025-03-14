#!/usr/bin/env bash

cd docker
docker build -t web-client-sided -t web-client-sided:latest -t git.ctf.umanitobacssa.ca/cssa/web-client-sided:latest .
docker compose up -d
docker compose down

cd ..

echo "The docker container has been built and pushed and is ready to be deployed."