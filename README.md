# Brainfuck Discord Bot

A simple discord bot with the back end written in brainfuck.

## Installing

If you want to use docker, just run `docker build . --build-arg token={Your token here}`, whenever you want to run the bot, run `docker run {Whatever the hell the container name is} -d -v {whatever the hell your log path is}:/var/log`.
If you don't want to use docker, you just have to do is compile bot.bf, whenever you want to run the bot, run `export BOT_TOKEN={Your token here}`, then `./start.sh`.
