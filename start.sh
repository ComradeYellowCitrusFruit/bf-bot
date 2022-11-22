#/bin/bash
mkfifo botpipe
python bot.py ${BOT_TOKEN} < botpipe | python bf.py bot.bf > botpipe