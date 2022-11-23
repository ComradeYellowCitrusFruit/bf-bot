# Base image
FROM python:latest

# Declare args
ARG token
ENV BOT_TOKEN=${token}

# Entrypoint
ENTRYPOINT /usr/bot/start.sh 

# Commands
RUN mkdir /usr/bot
RUN pip install discord
RUN apt-get install gcc

COPY start.sh /usr/bot
COPY bot.py /usr/bot
COPY bot.bf /usr/bot
COPY bf.c /usr/bot

WORKDIR /usr/bot
RUN gcc bf.c -o bf -Ofast
RUN ./bf bot.bf -o bot
