import discord
import sys

TOKEN = sys.argv[0]
log = open("/var/log/botlog", "a")

class botClient(discord.Client):
    async def on_message(self, message):
        if message.author == self.user:
            return

        if message.content[0] == '!':
            log.write('Recieved a command "{0}" from {1} at {2}\n'.format(message.content, message.author.id, message.created_at))
            print(message.content)
            if message.content[1] == 'v':
                await message.channel.send(input())
            else:
                return
        else:
            return

bot = botClient()
bot.run(TOKEN)