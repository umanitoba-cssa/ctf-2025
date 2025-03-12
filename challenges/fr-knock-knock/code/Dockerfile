FROM python:3.9-slim

WORKDIR /app

COPY port_knocker.py .

EXPOSE 3712/udp 5917/udp 8821/udp

CMD ["python3", "port_knocker.py"]