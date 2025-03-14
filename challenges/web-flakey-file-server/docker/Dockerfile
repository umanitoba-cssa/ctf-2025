FROM node:22-bullseye-slim

WORKDIR /

COPY ./app /app
COPY ./app/files /files
WORKDIR /app

RUN chown -R root:root /app
RUN chmod -R 755 /app
RUN npm ci

RUN useradd -ms /bin/bash nodeuser
USER nodeuser

CMD ["node", "index.js"]