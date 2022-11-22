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
RUN mkdir /usr/local/bot
RUN apt-get install python
RUN apt-get install pip
RUN pip install brainfuck-interpreter

COPY start.sh /usr/local/bot
COPY bot.py /usr/local/bot
COPY bot.bf /usr/local/bot
COPY bf.py /usr/local/bot