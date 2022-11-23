#/bin/bash
mkfifo botpipe
python bot.py ${BOT_TOKEN} < botpipe | ./bot > botpipe