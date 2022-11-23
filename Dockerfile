# Base image
FROM debian:latest

# Declare args
ARG token
ENV BOT_TOKEN=${token}

# Declare volumes
VOLUME /var/log

# Entrypoint
ENTRYPOINT /usr/local/bot/start.sh 

# Commands
RUN mkdir /usr/bot
RUN apt-get install python
RUN apt-get install pip
RUN apt-get install gcc

COPY start.sh /usr/bot
COPY bot.py /usr/bot
COPY bot.bf /usr/bot
COPY bf.c /usr/bot