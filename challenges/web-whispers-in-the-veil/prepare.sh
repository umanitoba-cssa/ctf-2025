#!/usr/bin/env bash

cd docker
docker build -t web-whispers-in-the-veil -t web-whispers-in-the-veil:latest -t git.ctf.umanitobacssa.ca/cssa/web-whispers-in-the-veil:latest .
docker compose up -d
docker compose down

cd ..

echo "The docker container has been built and pushed and is ready to be deployed."