#!/usr/bin/env bash

cd docker
docker compose up --build -d

cd ..
cd solution


if ./solution.py | grep -q 'cssactf{'; then
   RESULT="True"
else
   RESULT="False"
fi

cd ..
cd docker
docker compose down

cd ..

if [[ $RESULT -eq "True" ]]; then
   echo "Challenge validation passed, the solution works as expected."
else
   echo "The solution script may have failed, please review the output for errors. If you see the flag printed, then the challenge is working as expected."
fi